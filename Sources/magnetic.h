#ifndef MAGNETIC_H
#define MAGNETIC_H

// magnetic calibration constants
#if THIS_BOARD_ID != BOARD_FXLC95000CL
// Kinetis magnetic buffer parameters
#define MAGBUFFSIZEX 12					// x dimension in magnetometer buffer (12x24 equals 288 elements)
#define MAGBUFFSIZEY (2 * MAGBUFFSIZEX)	// y dimension in magnetometer buffer (12x24 equals 288 elements)
#define MINMEASUREMENTS4CAL 50			// minimum number of measurements for 4 element calibration
#define MINMEASUREMENTS7CAL 100			// minimum number of measurements for 7 element calibration
#define MINMEASUREMENTS10CAL 150		// minimum number of measurements for 10 element calibration
#define MAXMEASUREMENTS 240				// maximum number of measurements used for calibration
#else
// FXLC95000CL magnetic buffer parameters
#define MAGBUFFSIZEX 6					// x dimension in magnetometer buffer (6x12 equals 72 elements)
#define MAGBUFFSIZEY (2 * MAGBUFFSIZEX)	// y dimension in magnetometer buffer (6x12 equals 72 elements)
#define MINMEASUREMENTS4CAL 50			// minimum number of measurements for 4 element calibration
#define MINMEASUREMENTS7CAL 55			// minimum number of measurements for 7 element calibration
#define MINMEASUREMENTS10CAL 60			// minimum number of measurements for 10 element calibration
#define MAXMEASUREMENTS 65				// maximum number of measurements used for calibration
#endif

// parameters common to Kinetis and Galla
#define INTERVAL4CAL 75					// 2s at 25Hz: 4 element interval (samples)
#define INTERVAL7CAL 250				// 10s at 25Hz: 7 element interval (samples)
#define INTERVAL10CAL 750				// 30s at 25Hz: 10 element interval (samples)
#define MINBFITUT 10.0F					// minimum acceptable geomagnetic field B (uT) for valid calibration
#define MAXBFITUT 90.0F					// maximum acceptable geomagnetic field B (uT) for valid calibration
#define FITERRORAGINGSECS 1800.0F		// time (s) for fit error to increase (age) by e=2.718
#define MESHDELTACOUNTS 50				// magnetic buffer mesh spacing in counts (here 5uT) 

// magnetometer measurement buffer
struct MagneticBuffer
{
	int16 iBpFast[3][MAGBUFFSIZEX][MAGBUFFSIZEY];	// uncalibrated magnetometer readingss
	int32 index[MAGBUFFSIZEX][MAGBUFFSIZEY];		// array of time indices
	int16 tanarray[MAGBUFFSIZEX - 1];				// array of tangents of (100 * angle)
	int16 iMagBufferCount;							// number of magnetometer readings
};

// magnetic calibration structure
struct MagCalibration
{
	float fV[3];					// current hard iron offset x, y, z, (uT)
	float finvW[3][3];				// current inverse soft iron matrix
	float fB;						// current geomagnetic field magnitude (uT)
	float fFourBsq;					// current 4*B*B (uT^2)
	float fFitErrorpc;				// current fit error %
	float ftrV[3];					// trial value of hard iron offset z, y, z (uT)
	float ftrinvW[3][3];			// trial inverse soft iron matrix size
	float ftrB;						// trial value of geomagnetic field magnitude in uT
	float ftrFitErrorpc;			// trial value of fit error %
	float fA[3][3];					// ellipsoid matrix A
	float finvA[3][3];				// inverse of ellipsoid matrix A
	float fmatA[10][10];			// scratch 10x10 matrix used by calibration algorithms
	float fmatB[10][10];			// scratch 10x10 matrix used by calibration algorithms
	float fvecA[10];				// scratch 10x1 vector used by calibration algorithms
	float fvecB[4];					// scratch 4x1 vector used by calibration algorithms
	int8 iCalInProgress;			// flag denoting that a calibration is in progress
	int8 iMagCalHasRun;				// flag denoting that at least one calibration has been launched
	int8 iValidMagCal;				// integer value 0, 4, 7, 10 denoting both valid calibration and solver used
};

// function prototypes for function in magnetic.c
void fInitMagCalibration(struct MagCalibration *pthisMagCal, struct MagneticBuffer *pthisMagBuffer);
void iUpdateMagnetometerBuffer(struct MagneticBuffer *pthisMagBuffer, struct AccelSensor *pthisAccel,
		struct MagSensor *pthisMag, int32 loopcounter);
void fInvertMagCal(struct MagSensor *pthisMag, struct MagCalibration *pthisMagCal);
void fUpdateCalibration10EIG(struct MagCalibration *pthisMagCal, struct MagneticBuffer *pthisMagBuffer, struct MagSensor *pthisMag);
void fUpdateCalibration7EIG(struct MagCalibration *pthisMagCal, struct MagneticBuffer *pthisMagBuffer, struct MagSensor *pthisMag);
void fUpdateCalibration4INV(struct MagCalibration *pthisMagCal, struct MagneticBuffer *pthisMagBuffer, struct MagSensor *pthisMag);

#endif   // #ifndef MAGNETIC_H
