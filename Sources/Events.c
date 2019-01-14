#include "Cpu.h"
#include "Events.h"
#include "mqx_tasks.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "include_all.h"

/*
 ** ===================================================================
 **     Event       :  Cpu_OnNMIINT (module Events)
 **
 **     Component   :  Cpu [MKL25Z128LK4]
 **     Description :
 **         This event is called when the Non maskable interrupt had
 **         occurred. This event is automatically enabled when the <NMI
 **         interrupt> property is set to 'Enabled'.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */

// called on NMI (function for KL25 Freedom PCB)
void Cpu_OnNMIINT(void)
{
	// return with no action
	return;
}

/*
 ** ===================================================================
 **     Event       :  FTM0_sampling_OnCounterRestart (module Events)
 **
 **     Component   :  FTM0_sampling [TimerUnit_LDD]
 */
/*!
 **     @brief
 **         Called if counter overflow/underflow or counter is
 **         reinitialized by modulo or compare register matching.
 **         OnCounterRestart event and Timer unit must be enabled. See
 **         <SetEventMask> and <GetEventMask> methods. This event is
 **         available only if a <Interrupt> is enabled.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. The pointer passed as
 **                           the parameter of Init method.
 */
/* ===================================================================*/
void FTM_OnCounterRestart(LDD_TUserData *UserDataPtr)
{
	// this function is called (typically at 200Hz) by the hardware clock interrupt and drives the sensor
	// read function and indirectly the fusion and magnetic calibration functions which
	// are software locked to the sensor read process

	// for physical sensors, always enable the sensor read task
#if !defined SIMULATEDBT
	// update time stamp counter
	mqxglobals.FTM0_timestamp += (uint32)mqxglobals.FTM0Reload;
	// enable the (typically 200Hz) sensor read event FSL_SAMPLING_EVENT
	// with a mask of 1 (least significant bit set)
	_lwevent_set(&(mqxglobals.SamplingEventStruct), 1);
#endif

	// MATLAB: for simulated sensors, only enable the sensor read task when the bluetooth packet has arrived
	// this results in received Bluetooth packets clocking the algorithms rather than the 200Hz clock
#if defined SIMULATEDBT
	if (iBluetoothSensorPacketWaiting)
	{
		// reset the Bluetooth flag
		iBluetoothSensorPacketWaiting = 0;
		// update time stamp counter
		globals.FTM0_timestamp += (uint32)globals.FTM0Reload;
		// enable the sensor read event FSL_SAMPLING_EVENT to read the Bluetooth packet
		// with a mask of 1 (least significant bit set)
		_lwevent_set(&(globals.SamplingEventStruct), 1);
	}
#endif

	return;
}

/*
 ** ===================================================================
 **     Event       :  UART2_OnBlockSent (module Events)
 **
 **     Component   :  UART2 [Serial_LDD]
 */
/*!
 **     @brief
 **         This event is called after the last character from the
 **         output buffer is moved to the transmitter.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. This pointer is passed
 **                           as the parameter of Init method.
 */
/* ===================================================================*/
void UART_OnBlockSent(LDD_TUserData *UserDataPtr)
{
	// return with no action
	return;
}

/*
 ** ===================================================================
 **     Event       :  I2C2_OnMasterBlockSent (module Events)
 **
 **     Component   :  I2C2 [I2C_LDD]
 */
/*!
 **     @brief
 **         This event is called when I2C in master mode finishes the
 **         transmission of the data successfully. This event is not
 **         available for the SLAVE mode and if MasterSendBlock is
 **         disabled.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. This pointer is passed
 **                           as the parameter of Init method.
 */
/* ===================================================================*/
void I2C_OnMasterBlockSent(LDD_TUserData *UserDataPtr)
{
	// set the I2C data sent flag
	mqxglobals.I2C2_Status |= I2C_SENT_FLAG;

	return;
}

/*
 ** ===================================================================
 **     Event       :  I2C2_OnMasterBlockReceived (module Events)
 **
 **     Component   :  I2C2 [I2C_LDD]
 */
/*!
 **     @brief
 **         This event is called when I2C is in master mode and finishes
 **         the reception of the data successfully. This event is not
 **         available for the SLAVE mode and if MasterReceiveBlock is
 **         disabled.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. This pointer is passed
 **                           as the parameter of Init method.
 */
/* ===================================================================*/
void I2C_OnMasterBlockReceived(LDD_TUserData *UserDataPtr)
{
	// set the I2C data received flag
	mqxglobals.I2C2_Status |= I2C_RCVD_FLAG;

	return;
}

/*
 ** ===================================================================
 **     Event       :  I2C2_OnError (module Events)
 **
 **     Component   :  I2C2 [I2C_LDD]
 */
/*!
 **     @brief
 **         This event is called when an error (e.g. Arbitration lost)
 **         occurs. The errors can be read with GetError method.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. This pointer is passed
 **                           as the parameter of Init method.
 */
/* ===================================================================*/
void I2C_OnError(LDD_TUserData *UserDataPtr)
{
	// return with no action
	return;
}

/*
 ** ===================================================================
 **     Event       :  UART2_OnTxComplete (module Events)
 **
 **     Component   :  UART2 [Serial_LDD]
 */
/*!
 **     @brief
 **         This event indicates that the transmitter is finished
 **         transmitting all data, preamble, and break characters and is
 **         idle. It can be used to determine when it is safe to switch
 **         a line driver (e.g. in RS-485 applications).
 **         The event is available only when both <Interrupt
 **         service/event> and <Transmitter> properties are enabled.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. This pointer is passed
 **                           as the parameter of Init method.
 */
/* ===================================================================*/
void UART_OnTxComplete(LDD_TUserData *UserDataPtr)
{
#ifdef DEEPSLEEP
	SCB_SCR |= SCB_SCR_SLEEPDEEP_MASK; // Enable full STOP mode
#endif
	return;
}

/*
 ** ===================================================================
 **     Event       :  UART2_OnBlockReceived (module Events)
 **
 **     Component   :  UART2 [Serial_LDD]
 */
/*!
 **     @brief
 **         This event is called when the requested number of data is
 **         moved to the input buffer.  It operates as a simple command
 **         interpreter for this embedded application.  Please note that we
 **         do not do full decoding.  Rather, we look at just enough characters
 **         to differentiate between the possible commands.
 **         If no match is found, nothing is done and the command is ignored.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. This pointer is passed
 **                           as the parameter of Init method.
 */
/* ===================================================================*/
void UART_OnBlockReceived(LDD_TUserData *UserDataPtr)
{
	int32 isum;			// 32 bit identifier

	// this function is called when a complete UART2 Bluetooth block has been received which is either
	// 4 byte head command (physical sensors) or
	// 4 byte command plus 18 sensor data bytes (simulated sensors)

	// MATLAB: set the flag denoting that a Bluetooth sensor packet is ready
#if defined SIMULATEDBT
	iBluetoothSensorPacketWaiting = 1;
#endif

	// calculate a unique 32 bit identifier from the four command characters received
	isum = ((((((int32)sUARTInputBuf[0] << 8) + sUARTInputBuf[1]) << 8) + sUARTInputBuf[2]) << 8) + sUARTInputBuf[3];

	// execute the bluetooth command received
	switch (isum)
	{
	// "VG+ " = enable angular velocity packet transmission
	case ((((('V' << 8) + 'G') << 8) + '+') << 8) + ' ':
				globals.AngularVelocityPacketOn = true; 
	break;
	// "VG- " = disable angular velocity packet transmission
	case ((((('V' << 8) + 'G') << 8) + '-') << 8) + ' ':
				globals.AngularVelocityPacketOn = false; 
	break;
	// "DB+ " = enable debug packet transmission
	case ((((('D' << 8) + 'B') << 8) + '+') << 8) + ' ':
				globals.DebugPacketOn = true;
	break;
	// "DB- " = disable debug packet transmission
	case ((((('D' << 8) + 'B') << 8) + '-') << 8) + ' ':
				globals.DebugPacketOn = false; 
	break;
	// "Q3  " = transmit 3-axis accelerometer quaternion in standard packet
	case ((((('Q' << 8) + '3') << 8) + ' ') << 8) + ' ':
				globals.QuaternionPacketType = Q3;
	break;
	// "Q3M " = transmit 3-axis magnetometer quaternion in standard packet
	case ((((('Q' << 8) + '3') << 8) + 'M') << 8) + ' ':
				globals.QuaternionPacketType = Q3M;
	break;
	// "Q3G " = transmit 3-axis gyro quaternion in standard packet
	case ((((('Q' << 8) + '3') << 8) + 'G') << 8) + ' ':
				globals.QuaternionPacketType = Q3G; 
	break;
	// "Q6MA" = transmit 6-axis mag/accel quaternion in standard packet
	case ((((('Q' << 8) + '6') << 8) + 'M') << 8) + 'A':
				globals.QuaternionPacketType = Q6MA; 
	break;
	// Note: we have no Bluetooth command defined for the 6DOF Kalman eCompass Q6KA
	// but it's defined here for future upgrade
	case ((((('Q' << 8) + '6') << 8) + 'K') << 8) + 'A':
				globals.QuaternionPacketType = Q6KA; 
	break;	
	// "Q6AG" = transmit 6-axis accel/gyro quaternion in standard packet
	case ((((('Q' << 8) + '6') << 8) + 'A') << 8) + 'G':
				globals.QuaternionPacketType = Q6AG;
	break;
	// "Q9  " = transmit 9-axis quaternion in standard packet (default)
	case ((((('Q' << 8) + '9') << 8) + ' ') << 8) + ' ':
				globals.QuaternionPacketType = Q9;
	break;
	// "RPC+" = Roll/Pitch/Compass on
	case ((((('R' << 8) + 'P') << 8) + 'C') << 8) + '+':
				globals.RPCPacketOn = true; 
	break;
	// "RPC-" = Roll/Pitch/Compass off
	case ((((('R' << 8) + 'P') << 8) + 'C') << 8) + '-':
				globals.RPCPacketOn = false; 
	break;
	// "ALT+" = Altitude packet on
	case ((((('A' << 8) + 'L') << 8) + 'T') << 8) + '+':
				globals.AltPacketOn = true; 
	break;
	// "ALT-" = Altitude packet off
	case ((((('A' << 8) + 'L') << 8) + 'T') << 8) + '-':
				globals.AltPacketOn = false; 
	break;
	// "RST " = Soft reset
	case ((((('R' << 8) + 'S') << 8) + 'T') << 8) + ' ':	
				globals.QuaternionPacketType = Q9;
#if defined COMPUTE_3DOF_B_BASIC || defined COMPUTE_6DOF_GB_BASIC || defined COMPUTE_6DOF_GB_KALMAN || defined COMPUTE_9DOF_GBY_KALMAN
	fInitMagCalibration(&thisMagCal, &thisMagBuffer);
#endif
	globals.loopcounter = 0;
	break;
	default:
		// debug: use this to flag a corrupt packet
		break;
	}

	// tell MQX to receive bluetooth packets and generate the next callback event to this same function
	// when the specified number of bytes have been received. this function is non-blocking
#if !defined SIMULATEDBT
	// receive 4 bytes specifying the quaternion to be transmitted back
	UART_ReceiveBlock(UART_DeviceData, sUARTInputBuf, 4);
#else
	// MATLAB: receive 22 bytes specifying 4 bytes for quaternion plus 18 bytes for 3 sensors * xyz * 16 bit
	UART_ReceiveBlock(UART2_DeviceData, sUARTInputBuf, 22);
#endif

	return;
}
