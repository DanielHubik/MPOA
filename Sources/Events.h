#ifndef EVENTS_H
#define EVENTS_H

#ifdef LIBRARY
typedef void LDD_TUserData;            /*!< Pointer to this type specifies the user or RTOS specific data will be passed as an event or callback parameter. */
typedef void LDD_TDeviceData;          /*!< Pointer to private device structure managed and used by HAL components. */
#else
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
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
#endif

// function prototypes for Event.c
void Cpu_OnNMIINT(void);
void Cpu_OnNMIINT0(void);
void FTM_OnCounterRestart(LDD_TUserData *UserDataPtr);
void UART2_OnBlockSent(LDD_TUserData *UserDataPtr);
void I2C_OnMasterBlockSent(LDD_TUserData *UserDataPtr);
void I2C_OnMasterBlockReceived(LDD_TUserData *UserDataPtr);
void I2C_OnError(LDD_TUserData *UserDataPtr);
void UART_OnTxComplete(LDD_TUserData *UserDataPtr);
void UART_OnBlockReceived(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  I2C_OnMasterBlockSent (module Events)
**
**     Component   :  I2C [I2C_LDD]
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
void I2C_OnMasterBlockSent(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  I2C_OnMasterBlockReceived (module Events)
**
**     Component   :  I2C [I2C_LDD]
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
void I2C_OnMasterBlockReceived(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  UART_OnBlockReceived (module Events)
**
**     Component   :  UART [Serial_LDD]
*/
/*!
**     @brief
**         This event is called when the requested number of data is
**         moved to the input buffer.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void UART_OnBlockReceived(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  UART_OnBlockSent (module Events)
**
**     Component   :  UART [Serial_LDD]
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
void UART_OnBlockSent(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  UART_OnTxComplete (module Events)
**
**     Component   :  UART [Serial_LDD]
*/
/*!
**     @brief
**         This event indicates that the transmitter is finished
**         transmitting all data, preamble, and break characters and is
**         idle. It can be used to determine when it is safe to switch
**         a line driver (e.g. in RS-485 applications).
**         The event is available only when both [Interrupt
**         service/event] and [Transmitter] properties are enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void UART_OnTxComplete(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  FTM_OnCounterRestart (module Events)
**
**     Component   :  FTM [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void FTM_OnCounterRestart(LDD_TUserData *UserDataPtr);

#endif // #ifndef EVENTS_H
