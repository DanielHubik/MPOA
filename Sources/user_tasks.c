#include "Cpu.h"
#include "Events.h"
#include "mqx_tasks.h"
#include "UART.h"
#include "LED_RED.h"
#include "LED_GREEN.h"
#include "include_all.h"
#include "math.h"
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
#include "stdlib.h"
#include "stdio.h"

LDD_TDeviceData* PointerData1;
	LDD_TUserData *PointerUserData2;
	
float Pk=1;
float Ik=0.08;//0.04

float Memory;

float P=0;
float I=0;
float Sum;
float lax = 0;
float lay = 0;
float temp = 0;

void UserStartup(void)
{
	// The following UART functions initialize Bluetooth communications used by the
	// Freescale Xtrinsic Sensor Fusion Toolbox.  If the developer is not using the toolbox,
	// these can be removed.
	//
	// initialize BlueRadios Bluetooth module
	//BlueRadios_Init(UART_DeviceData);

	// put code here to be executed at the end of the RTOS startup sequence.
	//
	//LDD_TUserData *pwm;
	//LDD_TDeviceData *ptrNaPwm;
	// PUT YOUR CODE HERE
	PointerData1=PWM1_Init(PointerUserData2);
	//

	return;
}

void UserHighFrequencyTaskInit(void)
{
	// User code to be executed ONE TIME the first time the high frequency task is run.
	//
	// PUT YOUR CODE HERE
	
	//
	return;
}

void UserMediumFrequencyTaskInit(void)
{
	// User code to be executed ONE TIME the first time the medium frequency task is run
	//
	// PUT YOUR CODE HERE
	//
	
	// switch all three LEDs off
	LED_RED_SetVal(NULL);
	LED_GREEN_SetVal(NULL);

	return;
}


void UserHighFrequencyTaskRun(void)
{
	// The default frequency at which this code runs is 200Hz.
	// This code runs after sensors are sampled.
	// In general, try to keep "high intensity" code out of UserHighFrequencyTaskRun.
	// The high frequency task also has highest priority.
	//
	// PUT YOUR CODE HERE
	
	int8 direction;
	lay = thisSV_9DOF_GBY_KALMAN.faSePl[Y];
	//9DOF accelerometer, magnetometer and gyro (Kalman) structure
	temp=abs((int)(lay*100));
	if(lay>0){
		direction=1;
	}else{
		direction=-1;
	}
	P=-temp*Pk;
	
	I=I+(int)lay*-100*Ik;
	if(I>100){
		I=100;
	}
	if(I<-100){
		I=-100;
	}
	Sum=(P+I);
	if(Sum>=100){
		Sum=100;
	}
	if(Sum<=-100){
		Sum=-100;
	}
	uint16 Set =  abs(65535-abs(Sum)*655);
	PWM1_SetRatio16(PointerData1,Set);
	//0-65535 655*100=65535

	if(direction==-1){
		//PWM1_ConnectPin(Pointer, Maska na piny);
		//
		Bit1_SetVal();
		Bit2_ClrVal();
		//reverse
	}else{
		//PWM1_ConnectPin(Pointer, Maska na piny);
		//
		Bit2_SetVal();
		Bit1_ClrVal();
	}
	return;
}

void UserMediumFrequencyTaskRun(void)
{
	
	// This code runs after the Kalman filter loop
	// The default frequency at which this code runs is 25Hz.
	
	// The following UART function constructs and sends Bluetooth packets used by the
	// Freescale Xtrinsic Sensor Fusion Toolbox.  If the developer is not using the toolbox,
	// it can be removed.
	// transmit orientation over the radio link
	//CreateAndSendBluetoothPacketsViaUART(UART_DeviceData);

	//
	// PUT YOUR CODE HERE
	//

	/*
	// Read Accelerometer Outputs [g]
	float ax = thisAccel.fGp[X];
	float ay = thisAccel.fGp[Y];
	float az = thisAccel.fGp[Z];

	// Read Gyroscope Outputs [deg/s]
	float omegax = thisGyro.fYp[X];
	float omegay = thisGyro.fYp[Y];
	float omegaz = thisGyro.fYp[Z];

	// Read Magnetometer Outputs [uT]
	float magx = thisMag.fBp[X];
	float magy = thisMag.fBp[Y];
	float magz = thisMag.fBp[Z];

	// Read Calibrated Magnetometer Outputs [uT]
	float cmagx = thisMag.fBc[X];
	float cmagy = thisMag.fBc[Y];
	float cmagz = thisMag.fBc[Z];

	// Read Linear Acceleration [g]
	float lax = thisSV_9DOF_GBY_KALMAN.faSePl[X];
	float lay = thisSV_9DOF_GBY_KALMAN.faSePl[Y];
	float laz = thisSV_9DOF_GBY_KALMAN.faSePl[Z];
	
	// Read Angular Velocity [deg/s]
	float omgx = thisSV_9DOF_GBY_KALMAN.fOmega[X];
	float omgy = thisSV_9DOF_GBY_KALMAN.fOmega[Y];
	float omgz = thisSV_9DOF_GBY_KALMAN.fOmega[Z];

	// Read Euler Angles [deg]
	float roll = thisSV_9DOF_GBY_KALMAN.fPhiPl;
	float pitch = thisSV_9DOF_GBY_KALMAN.fThePl;
	float yaw = thisSV_9DOF_GBY_KALMAN.fPsiPl;
  */	

	/*
	// Set LEDs on
	LED_BLUE_ClrVal(NULL);
	LED_GREEN_ClrVal(NULL);
	LED_RED_ClrVal(NULL);
	*/
	
	//lay = thisSV_9DOF_GBY_KALMAN.faSePl[Z];	
	//lay = thisSV_9DOF_GBY_KALMAN.faSePl[X];

	
	
	char s[128];
	uint16_t len;
	
	if(UP_GetVal()){
		//DOSEL PRIKAZ UP Z ARDUINA
;
	}else{
		//DOSEL PRIKAZ DOWN Z ARDUINA
		;
		
	}
	len=sprintf(s,"sum=%.3f \t\t Y=%d\n",Sum,(int)temp);
	UART_SendBlock(UART_DeviceData, s, len);
	//(LDD_TDeviceData *DeviceDataPtr, LDD_TData *BufferPtr, uint16_t Size)

	
	return;
}
