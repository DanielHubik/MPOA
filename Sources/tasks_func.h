#ifndef TASKS_FUNC_H
#define TASKS_FUNC_H

// structure definitions

// 1DOF pressure state vector structure
struct SV_1DOF_P_BASIC
{
	float fLPHp;					// low pass filtered height (m)
	float fLPTp;					// low pass filtered temperature (C);				
	float fdeltat;					// time interval (s)
	float flpf;						// low pass filter coefficient
	int32 systick;					// systick timer
};

// 3DOF basic accelerometer state vector structure
struct SV_3DOF_G_BASIC
{
	// start: elements common to all motion state vectors
	// Euler angles
	float fLPPhi;					// low pass roll (deg)
	float fLPThe;					// low pass pitch (deg)
	float fLPPsi;					// low pass yaw (deg)
	float fLPRho;					// low pass compass (deg)
	float fLPChi;					// low pass tilt from vertical (deg)
	// orientation matrix, quaternion and rotation vector
	float fLPR[3][3];				// low pass filtered orientation matrix
	struct fquaternion fLPq;		// low pass filtered orientation quaternion
	float fLPRVec[3];				// rotation vector
	// angular velocity
	float fOmega[3];				// angular velocity (deg/s)
	// systick timer for benchmarking
	int32 systick;					// systick timer
	// end: elements common to all motion state vectors
	float fR[3][3];					// unfiltered orientation matrix
	struct fquaternion fq;			// unfiltered orientation quaternion
	float fdeltat;					// time interval (s)
	float flpf;						// low pass filter coefficient
};

// 3DOF basic magnetometer state vector structure
struct SV_3DOF_B_BASIC
{
	// start: elements common to all motion state vectors
	// Euler angles
	float fLPPhi;						// low pass roll (deg)
	float fLPThe;						// low pass pitch (deg)
	float fLPPsi;						// low pass yaw (deg)
	float fLPRho;						// low pass compass (deg)
	float fLPChi;						// low pass tilt from vertical (deg)
	// orientation matrix, quaternion and rotation vector
	float fLPR[3][3];					// low pass filtered orientation matrix
	struct fquaternion fLPq;			// low pass filtered orientation quaternion
	float fLPRVec[3];					// rotation vector
	// angular velocity
	float fOmega[3];					// angular velocity (deg/s)
	// systick timer for benchmarking
	int32 systick;						// systick timer
	// end: elements common to all motion state vectors
	float fR[3][3];						// unfiltered orientation matrix
	struct fquaternion fq;				// unfiltered orientation quaternion
	float fdeltat;						// time interval (s)
	float flpf;							// low pass filter coefficient
};

// 3DOF basic gyroscope state vector structure
struct SV_3DOF_Y_BASIC
{
	// start: elements common to all motion state vectors
	// Euler angles
	float fPhi;						// roll (deg)
	float fThe;						// pitch (deg)
	float fPsi;						// yaw (deg)
	float fRho;						// compass (deg)
	float fChi;						// tilt from vertical (deg)
	// orientation matrices and quaternions
	float fR[3][3];					// unfiltered orientation matrix
	struct fquaternion fq;			// unfiltered orientation quaternion
	float fRVec[3];					// rotation vector
	// angular velocity
	float fOmega[3];				// angular velocity (deg/s)
	// systick timer for benchmarking
	int32 systick;					// systick timer
	// end: elements common to all motion state vectors
	struct fquaternion fDeltaq;		// delta rotation quaternion
	float fFastdeltat;				// sensor sampling interval (s) = 1 / SENSORFS
	float fdeltat;					// kalman filter sampling interval (s) = OVERSAMPLE_RATIO / SENSORFS
};

// 6DOF basic accelerometer and magnetometer state vector structure
struct SV_6DOF_GB_BASIC
{
	// start: elements common to all motion state vectors
	// Euler angles
	float fLPPhi;					// low pass roll (deg)
	float fLPThe;					// low pass pitch (deg)
	float fLPPsi;					// low pass yaw (deg)
	float fLPRho;					// low pass compass (deg)
	float fLPChi;					// low pass tilt from vertical (deg)
	// orientation matrix, quaternion and rotation vector
	float fLPR[3][3];				// low pass filtered orientation matrix
	struct fquaternion fLPq;		// low pass filtered orientation quaternion
	float fLPRVec[3];				// rotation vector
	// angular velocity
	float fOmega[3];				// virtual gyro angular velocity (deg/s)
	// systick timer for benchmarking
	int32 systick;					// systick timer
	// end: elements common to all motion state vectors
	float fR[3][3];					// unfiltered orientation matrix
	struct fquaternion fq;			// unfiltered orientation quaternion
	float fDelta;					// unfiltered inclination angle (deg)
	float fLPDelta;					// low pass filtered inclination angle (deg)
	float fdeltat;					// time interval (s)
	float flpf;						// low pass filter coefficient
};

// 6DOF Kalman filter accelerometer and magnetometer state vector structure
struct SV_6DOF_GB_KALMAN
{
	// start: elements common to all motion state vectors
	// Euler angles
	float fPhiPl;					// roll (deg)
	float fThePl;					// pitch (deg)
	float fPsiPl;					// yaw (deg)
	float fRhoPl;					// compass (deg)
	float fChiPl;					// tilt from vertical (deg)
	// orientation matrix, quaternion and rotation vector
	float fRPl[3][3];				// a posteriori  rotation matrix
	struct fquaternion fqPl;		// a posteriori orientation quaternion
	float fRVecPl[3];				// rotation vector
	// angular velocity
	float fOmegaPl[3];				// a posteriori angular velocity (deg/s)
	// systick timer for benchmarking
	int32 systick;					// systick timer
	// end: elements common to all motion state vectors
	float fDelta;					// inclination angle (deg)
	float fLPDelta;					// low pass inclination angle (deg)
	float fzErrMi[3];				// angular error (deg) between a priori and eCompass orientations
	float fR[3][3];					// unfiltered eCompass rotation matrix
	float fRMi[3][3];				// a priori rotation matrix
	float fDeltaR[3][3];			// delta rotation matrix
	float fDeltaRMi[3][3];			// delta a priori omega*dt rotation matrix
	float fDeltaRPl[3][3];			// delta a posterori theta error+ rotation matrix
	struct fquaternion fqMi;		// a priori orientation quaternion
	struct fquaternion fDeltaq;		// delta a priori or a posteriori quaternion
	float fThErrPl[3];				// a posteriori orientation error (deg)
	float fOmegaErrPl[3];			// a posteriori angular velocity error (deg/s)
	float fOmegaMi[3];				// a priori angular velocity (deg/s)
	float fPPlus6x6[6][6];			// covariance matrix P+
	float fK6x3[6][3];				// kalman filter gain matrix K
	float fQw6x6[6][6];				// covariance matrix Qw
	float fdeltat;					// kalman filter sampling interval (s) = OVERSAMPLE_RATIO / SENSORFS
	float fdeltatsq;				// fdeltat * fdeltat;
	float fcomegasq;				// FCOMEGA * FCOMEGA
	float fKalmanFS;				// kalman filter sampling interval (s) = SENSORFS / OVERSAMPLE_RATIO
	float flpf;						// low pass filter coefficient (for Delta only)
};

// 6DOF Kalman filter accelerometer and gyroscope state vector structure
struct SV_6DOF_GY_KALMAN
{
	// start: elements common to all motion state vectors
	// Euler angles
	float fPhiPl;					// roll (deg)
	float fThePl;					// pitch (deg)
	float fPsiPl;					// yaw (deg)
	float fRhoPl;					// compass (deg)
	float fChiPl;					// tilt from vertical (deg)
	// orientation matrix, quaternion and rotation vector
	float fRPl[3][3];				// a posteriori  rotation matrix
	struct fquaternion fqPl;		// a posteriori orientation quaternion
	float fRVecPl[3];				// rotation vector
	// angular velocity
	float fOmega[3];				// angular velocity (deg/s)
	// systick timer for benchmarking
	int32 systick;					// systick timer
	// end: elements common to all motion state vectors
	
	// elements transmitted over bluetooth in kalman packet
	float fbPl[3];					// gyro offset (deg/s)
	float fThErrPl[3];				// orientation error (deg)
	float fbErrPl[3];				// gyro offset error (deg/s)
	// end elements transmitted in kalman packet
	
	float fzErrMi[3];				// angular error (deg) between a priori and eCompass orientations
	float fRMi[3][3];				// a priori rotation matrix
	float fDeltaRMi[3][3];			// delta a priori omega*dt rotation matrix
	float fDeltaRPl[3][3];			// delta a posterori theta error+ rotation matrix
	struct fquaternion fqMi;		// a priori orientation quaternion
	struct fquaternion fDeltaq;		// delta a priori or a posteriori quaternion
	
	float faSePl[3];				// linear acceleration (g, sensor frame)

	float faErrSePl[3];				// linear acceleration error (g, sensor frame)
	float fgErrSeMi[3];				// difference (g, sensor frame) of gravity vector (accel) and gravity vector (gyro)
	float fgSeGyMi[3];				// gravity vector (g, sensor frame) measurement from gyro
	float faSeMi[3];				// linear acceleration (g, sensor frame)
	float fQvAA;					// accelerometer terms of Qv
	float fPPlus9x9[9][9];			// covariance matrix P+
	float fK9x3[9][3];				// kalman filter gain matrix K
	float fQw9x9[9][9];				// covariance matrix Qw
	float fcasq;					// FCA * FCA;
	float fFastdeltat;				// sensor sampling interval (s) = 1 / SENSORFS
	float fdeltat;					// kalman filter sampling interval (s) = OVERSAMPLE_RATIO / SENSORFS
	float fdeltatsq;				// fdeltat * fdeltat;
	float fQwbplusQvG;				// FQWB + FQVG;
	int16 iFirstOrientationLock;	// denotes that 6DOF orientation has locked to 3DOF
};

// 9DOF Kalman filter accelerometer, magnetometer and gyroscope state vector structure
struct SV_9DOF_GBY_KALMAN
{
	// start: elements common to all motion state vectors
	// Euler angles
	float fPhiPl;					// roll (deg)
	float fThePl;					// pitch (deg)
	float fPsiPl;					// yaw (deg)
	float fRhoPl;					// compass (deg)
	float fChiPl;					// tilt from vertical (deg)
	// orientation matrix, quaternion and rotation vector
	float fRPl[3][3];				// a posteriori orientation matrix
	struct fquaternion fqPl;		// a posteriori orientation quaternion
	float fRVecPl[3];				// rotation vector
	// angular velocity
	float fOmega[3];				// angular velocity (deg/s)
	// systick timer for benchmarking
	int32 systick;					// systick timer;
	// end: elements common to all motion state vectors
	
	// elements transmitted over bluetooth in kalman packet
	float fbPl[3];					// gyro offset (deg/s)
	float fThErrPl[3];				// orientation error (deg)
	float fbErrPl[3];				// gyro offset error (deg/s)
	// end elements transmitted in kalman packet
	
	float fdErrGlPl[3];				// magnetic disturbance error (uT, global frame)
	float fdErrSePl[3];				// magnetic disturbance error (uT, sensor frame)
	float faErrSePl[3];				// linear acceleration error (g, sensor frame)
	float fdSeMi[3];				// magnetic disturbance (uT, sensor frame)
	float faSeMi[3];				// linear acceleration (g, sensor frame)
	float fDeltaPl;					// inclination angle (deg)
	float faSePl[3];				// linear acceleration (g, sensor frame)
	float faGlPl[3];				// linear acceleration (g, global frame)
	float fvGlPl[3];				// velocity (m/s, global frame)
	float frGlPl[3];				// displacement (m, global frame)
	float fLPaGlPl[3];				// low pass linear acceleration (g, global frame)
	float fLPvGlPl[3];				// low pass velocity (m/s, global frame)
	float fgErrSeMi[3];				// difference (g, sensor frame) of gravity vector (accel) and gravity vector (gyro)
	float fmErrSeMi[3];				// difference (uT, sensor frame) of geomagnetic vector (magnetometer) and geomagnetic vector (gyro)
	float fgSeGyMi[3];				// gravity vector (g, sensor frame) measurement from gyro
	float fmSeGyMi[3];				// geomagnetic vector (uT, sensor frame) measurement from gyro
	float fgGlz;					// z component of gravity vector (g, global frame)
	float fmGl[3];					// geomagnetic vector (uT, global frame)
	float fQvAA;					// accelerometer terms of Qv
	float fQvMM;					// magnetometer terms of Qv
	float fPPlus12x12[12][12];		// covariance matrix P+
	float fK12x6[12][6];			// kalman filter gain matrix K
	float fQw12x12[12][12];			// covariance matrix Qw
	float fRMi[3][3];				// a priori orientation matrix
	float fDeltaRMi[3][3];			// delta a priori omega*dt rotation matrix
	float fDeltaRPl[3][3];			// delta a posterori theta error+ rotation matrix
	struct fquaternion fDeltaq;		// delta quaternion
	struct fquaternion fqMi;		// a priori orientation quaternion
	float fcasq;					// FCA * FCA;
	float fcdsq;					// FCD * FCD;
	float fFastdeltat;				// sensor sampling interval (s) = 1 / SENSORFS
	float fdeltat;					// kalman filter sampling interval (s) = OVERSAMPLE_RATIO / SENSORFS
	float fdeltatsq;				// fdeltat * fdeltat
	float fQwbplusQvG;				// FQWB + FQVG
	int16 iFirstOrientationLock;	// denotes that 9DOF orientation has locked to 6DOF
};

// globals defined in tasks_func.c declared here for use elsewhere
extern struct PressureSensor thisPressure;   
extern struct AccelSensor thisAccel;   
extern struct MagSensor thisMag;       
extern struct GyroSensor thisGyro;     
extern struct MagCalibration thisMagCal;
extern struct MagneticBuffer thisMagBuffer;
extern int8 iBluetoothSensorPacketWaiting; // MATLAB

extern struct SV_1DOF_P_BASIC thisSV_1DOF_P_BASIC;
extern struct SV_3DOF_G_BASIC thisSV_3DOF_G_BASIC;
extern struct SV_3DOF_B_BASIC thisSV_3DOF_B_BASIC;
extern struct SV_3DOF_Y_BASIC thisSV_3DOF_Y_BASIC;
extern struct SV_6DOF_GB_BASIC thisSV_6DOF_GB_BASIC;
extern struct SV_6DOF_GB_KALMAN thisSV_6DOF_GB_KALMAN;
extern struct SV_6DOF_GY_CC thisSV_6DOF_GY_CC;
extern struct SV_6DOF_GY_KALMAN thisSV_6DOF_GY_KALMAN;
extern struct SV_9DOF_GBY_KALMAN thisSV_9DOF_GBY_KALMAN;

// function prototypes for functions in tasks_func.c
void ApplyAccelHAL(struct AccelSensor *pthisAccel);
void ApplyMagHAL(struct MagSensor *pthisMag);
void ApplyGyroHAL(struct GyroSensor *pthisGyro, int16 irow);
void RdSensData_Init(void);
void RdSensData_Run(void);
void Fusion_Init(void);
void Fusion_Run(void);
void MagCal_Run(struct MagCalibration *pthisMagCal, struct MagneticBuffer *pthisMagBuffer);

#endif   // #ifndef TASKS_FUNC_H
