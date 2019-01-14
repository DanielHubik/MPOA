#ifndef MQX_TASKS_H
#define MQX_TASKS_H

#ifdef LIBRARY
typedef unsigned long  boolean;  /* Machine representation of a boolean */
#include "stdint.h"
#else
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"
#include "MQX1.h"
#include "SystemTimer1.h"
#include "LED_RED.h"
#include "LED_GREEN.h"
#include "UART.h"
#include "I2C.h"
#include "TestPin_KF_Time.h"
#include "TestPin_MagCal_Time.h"
#include "UP.h"
#include "BitIoLdd1.h"
#include "DOWN.h"
#include "BitIoLdd2.h"
#include "LEFT.h"
#include "BitIoLdd3.h"
#include "RIGHT.h"
#include "BitIoLdd4.h"
#include "FTM.h"
#include "PWM1.h"
#include "TU1.h"
#include "Bit1.h"
#include "BitIoLdd5.h"
#include "Bit2.h"
#include "BitIoLdd6.h"
#include "lwevent.h"
#endif
#include "proj_config.h"

// project globals structure
struct ProjectGlobals
{
	// bluetooth flags
	boolean AngularVelocityPacketOn;
	boolean DebugPacketOn;
	boolean RPCPacketOn;
	boolean AltPacketOn;

	// bluetooth quaternion type
	quaternion_type QuaternionPacketType;

	// magnetic packet variable identifier
	int16 MagneticPacketID;

	// bluetooth packet number
	uint8 iBluetoothPacketNumber;  	

	// MPL3115 found flag
	uint8 iMPL3115Found; 
	
	// global counter incrementing each iteration of sensor fusion (typically 25Hz)
	int32 loopcounter;
};

#ifndef LIBRARY
// mqx-lite globals structure
struct MQXLiteGlobals
{
	// MQX-Lite Events
	LWEVENT_STRUCT SamplingEventStruct;	// hardware timer event
	LWEVENT_STRUCT RunKFEventStruct;	// kalman filter sensor fusion event
	LWEVENT_STRUCT MagCalEventStruct;	// magnetic calibration event

	// FTM0 hardware time globals
	uint16 FTM0Reload;               	// FTM0 wraparound reload value
	uint32 FTM0_timestamp ;   			// time stamp updated from FTM0

	// flags
	volatile uint8 I2C2_Status;
	volatile uint16 RunKF_Event_Flag;
	volatile uint16 MagCal_Event_Flag;
};
// globals defined in mqx_tasks.c
extern struct MQXLiteGlobals mqxglobals;
#endif

// globals defined in mqx_tasks.c
extern struct ProjectGlobals globals;

// function prototypes for functions in mqx_tasks.c
void Main_task(uint32_t task_init_data);
void RdSensData_task(uint32_t task_init_data);
void Fusion_task(uint32_t task_init_data);
void MagCal_task(uint32_t task_init_data);

#endif // MQX_TASKS_H
