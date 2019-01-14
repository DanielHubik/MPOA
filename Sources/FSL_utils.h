#ifndef FSL_UTILS_H
#define FSL_UTILS_H

// compile time constants
#define I2C2_BUF_LEN           16
#define UART_INPUT_BUFFER_SIZE 	4	// MATLAB: needs to be increased to 22 when PC code is ready
#define UART_OUTPUT_BUFFER_SIZE 256
#define I2C_SENT_FLAG       0x01
#define I2C_RCVD_FLAG       0x02

// globals defined in FSL_utils.c
extern uint8 sUARTOutputBuf[UART_OUTPUT_BUFFER_SIZE];
extern uint8 sUARTInputBuf[UART_INPUT_BUFFER_SIZE];

// functions defined in FSL_utils.c
uint8 MPL3115_Init(LDD_TDeviceData *DeviceDataPtr, struct PressureSensor *pthisPressure);
void FXOS8700_Init(LDD_TDeviceData *DeviceDataPtr, struct AccelSensor *pthisAccel, struct MagSensor *pthisMag);
void FXAS21000_Init(LDD_TDeviceData *DeviceDataPtr, struct GyroSensor *pthisGyro);
void FXAS21002_Init(LDD_TDeviceData *DeviceDataPtr, struct GyroSensor *pthisGyro);
void MMA8652_Init(LDD_TDeviceData *DeviceDataPtr, struct AccelSensor *pthisAccel);
void MAG3110_Init(LDD_TDeviceData *DeviceDataPtr, struct MagSensor *pthisMag);
void MPL3115_ReadData(LDD_TDeviceData *DeviceDataPtr, struct PressureSensor *pthisPressure);
void FXOS8700_ReadData(LDD_TDeviceData *DeviceDataPtr, struct AccelSensor *pthisAccel, struct MagSensor *pthisMag);
void FXAS21000_ReadData(LDD_TDeviceData *DeviceDataPtr, struct GyroSensor *pthisGyro, int16 irow);
void FXAS21002_ReadData(LDD_TDeviceData *DeviceDataPtr, struct GyroSensor *pthisGyro, int16 irow);
void MMA8652_ReadData(LDD_TDeviceData *DeviceDataPtr, struct AccelSensor *pthisAccel);
void MAG3110_ReadData(LDD_TDeviceData *DeviceDataPtr, struct MagSensor *pthisMag);
void ReadBluetoothAccelData(struct AccelSensor *pthisAccel);
void ReadBluetoothMagData(struct MagSensor *pthisMag);
void ReadBluetoothGyroData(struct GyroSensor *pthisGyro, int16 irow);
void sBufAppendItem(uint8* pDest, uint32* pIndex, uint8* pSource, uint16 iBytesToCopy);
void BlueRadios_Init(LDD_TDeviceData *DeviceDataPtr);
void CreateAndSendBluetoothPacketsViaUART(LDD_TDeviceData *DeviceDataPtr);

#endif // FSL_UTILS_H
