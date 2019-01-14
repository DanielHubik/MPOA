#include "Cpu.h"
#include "Events.h"
#include "mqx_tasks.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stdio.h>
#include "I2C.h"
#include "UART.h"
#include "FTM.h"
#include "include_all.h"

// MQX-Lite globals structure
struct ProjectGlobals globals;
struct MQXLiteGlobals mqxglobals;

// Main task
void Main_task(uint32_t task_init_data)
{
	// create the sensor sampling event (typically 200Hz)
	_lwevent_create(&(mqxglobals.SamplingEventStruct), LWEVENT_AUTO_CLEAR);
	// create the Kalman filter sensor fusion event (typically 25Hz)
	_lwevent_create(&(mqxglobals.RunKFEventStruct), LWEVENT_AUTO_CLEAR);
	// create the magnetic calibration event (typically once per minute)
	_lwevent_create(&(mqxglobals.MagCalEventStruct), LWEVENT_AUTO_CLEAR);

	// create the sensor read task (controlled by sensor sampling event SamplingEventStruct)
	// on 12/12/2013 RDSENSDATA_TASK_STACK_SIZE was approx 768 bytes stack
	_task_create_at(0, RDSENSDATA_TASK, 0, RdSensData_task_stack, RDSENSDATA_TASK_STACK_SIZE);
	// create the sensor fusion task (controlled by sensor fusion event RunKFEventStruct)
	// on 12/12/2013 FUSION_TASK_STACK_SIZE was approx 1024 bytes stack
	_task_create_at(0, FUSION_TASK, 0, Fusion_task_stack, FUSION_TASK_STACK_SIZE);
	// create the magnetic calibration task (controlled by MagCalEventStruct)
	// on 12/12/2013 MAGCAL_TASK_STACK_SIZE was approx 768 bytes stack
	_task_create_at(0, MAGCAL_TASK, 0, MagCal_task_stack, MAGCAL_TASK_STACK_SIZE);
	// and this main task uses about 512 bytes stack for a grand total of 3K task stack space

	// set the sensor sampling frequency (typically 200Hz)
	// this is set to 200Hz by default in PE but we want to set it using value in proj_config.h 
	FTM_SetPeriodTicks(FTM_DeviceData, (uint16) (FTM_INCLK_HZ / SENSORFS));
	
	// initialize globals
	mqxglobals.FTM0Reload = (uint16)(FTM_INCLK_HZ / SENSORFS);
	mqxglobals.FTM0_timestamp = 0;
	globals.iBluetoothPacketNumber = 0;
	globals.AngularVelocityPacketOn = false;
	globals.DebugPacketOn = false;
	globals.RPCPacketOn = false;
	globals.AltPacketOn = true;
	globals.QuaternionPacketType = Q9;
	globals.iMPL3115Found = false;
	globals.MagneticPacketID = 0;

	// initialize the BlueRadios Bluetooth module and other user tasks
	UserStartup();

	// destroy this task (main task) now that the three new tasks are created
	_task_destroy(MQX_NULL_TASK_ID);

	return;
}

// sensor read task
void RdSensData_task(uint32_t task_init_data)
{
	// initialize the physical sensors over I2C and the sensor data structures
	RdSensData_Init();

	// initialize the user high frequency (typically 200Hz) task
	UserHighFrequencyTaskInit();

	// loop indefinitely (typically 200Hz)
	while(1)
	{
		// wait here for the sampling event (hardware clock, typically at 200Hz)
		// the Kalman filter and magnetic fusion tasks execute while this task is blocked here
		// FALSE means any bit (of the 1 bit enabled by the mask) unblocks
		// and NULL means timeout is infinite
		_lwevent_wait_for(&(mqxglobals.SamplingEventStruct), 1, FALSE, NULL);

		// reset the Kalman filter task flag
		mqxglobals.RunKF_Event_Flag = 0;
		// read the sensors
		RdSensData_Run();
		// run the user high frequency task
		UserHighFrequencyTaskRun();

		// use the Kalman filter flag set by the sensor read task (typically every 8 iterations)
		// with a mask of 1 (least significant bit set) to enable the Kalman filter task to run
		if (mqxglobals.RunKF_Event_Flag)
			_lwevent_set(&(mqxglobals.RunKFEventStruct), 1);

	}  // end of infinite loop
}

// Kalman filter sensor fusion task
void Fusion_task(uint32_t task_init_data)
{
	// initialize the sensor fusion algorithms
	Fusion_Init();

	// initialize the user medium frequency (typically 25Hz) task
	UserMediumFrequencyTaskInit();

	// infinite loop controlled by MQX-Lite events
	while(1)
	{
		TestPin_KF_Time_ClrVal(NULL);  // KF TEST PIN LOW

		// wait for the sensor fusion event to occur
		// FALSE means any bit (of the 1 bit enabled by the mask) unblocks
		// and NULL means timeout is infinite
		_lwevent_wait_for(&(mqxglobals.RunKFEventStruct), 1, FALSE, NULL);

		TestPin_KF_Time_SetVal(NULL);  // KF TEST PIN HI

		// reset the magnetic calibration flag (this is set by the fusion algorithm)
		mqxglobals.MagCal_Event_Flag = 0;
		// call the sensor fusion algorithms
		Fusion_Run();

		// run the user medium frequency (typically 25Hz) user task
		UserMediumFrequencyTaskRun();

		// enable the magnetic calibration event if the flag for a new magnetic calibration
		// with a mask of 1 (least significant bit set)
		// was set by the sensor fusion algorithms
		if (mqxglobals.MagCal_Event_Flag)
		{
			_lwevent_set(&(mqxglobals.MagCalEventStruct), 1);
		}

	} // end of infinite loop

	return;
}

// magnetic calibration task
void MagCal_task(uint32_t task_init_data)
{
	while(1)
	{
		TestPin_MagCal_Time_ClrVal(NULL);  // MAG CAL TEST PIN LOW

		// wait for the magnetic calibration event
		// this event will never be enabled for build options which don't require magnetic calibration
		// FALSE means any bit (of the 1 bit enabled by the mask) unblocks
		// and NULL means timeout is infinite
		_lwevent_wait_for(&(mqxglobals.MagCalEventStruct), 1, FALSE, NULL);

		TestPin_MagCal_Time_SetVal(NULL);  // MAG CAL TEST PIN HI

		// prevent compilation errors when magnetic calibration is not required
#if defined COMPUTE_6DOF_GB_BASIC || defined COMPUTE_6DOF_GB_KALMAN || defined COMPUTE_9DOF_GBY_KALMAN
		// and run the magnetic calibration
		MagCal_Run(&thisMagCal, &thisMagBuffer);
#endif

	} // end of infinite loop

	return;
}
