#ifndef BARANSKI_KALMAN_H
#define BARANSKI_KALMAN_H

// *********************************************************************************
// COMPUTE_6DOF_GB_KALMAN constants
// *********************************************************************************
// kalman filter noise variances
#define FQVTH_6DOF_GB_KALMAN 1.0F				// 1.0F: eCompass angular jitter (deg^2)
#define FQWOMEGA_6DOF_GB_KALMAN 7.0F 			// 10.0F: angular velocity random walk variance (deg/s)^2
#define FCOMEGA_6DOF_GB_KALMAN 0.7F				// 0.7F angular velocity decay factor
// initialization of Qw covariance matrix
#define FQWINITTHTH_6DOF_GB_KALMAN 0.15F		// 0.15F: th_e * th_e terms
#define FQWINITOMEGAOMEGA_6DOF_GB_KALMAN 15.0F	// 15.0F: omega_e * omega_e terms
#define FQWINITTHOMEGA_6DOF_GB_KALMAN 0.5F		// 0.5: th_e * omega_e terms

// *********************************************************************************
// COMPUTE_6DOF_GY_KALMAN constants
// *********************************************************************************
// kalman filter noise variances
#define FQVA_6DOF_GY_KALMAN 2E-6F				// 2E-6: accelerometer noise g^2 so 1.4mg RMS
#define FQVG_6DOF_GY_KALMAN 0.3F				// 0.3: gyro noise (deg/s)^2
#define FQWB_6DOF_GY_KALMAN 1E-9F				// 1E-10: gyro offset drift (deg/s)^2: 1E-9 implies 0.09deg/s max at 50Hz
#define FQWA_6DOF_GY_KALMAN 1E-4F				// 1E-4: linear acceleration drift g^2 (increase slows convergence to g but reduces sensitivity to shake)
// initialization of Qw covariance matrix
#define FQWINITTHTH_6DOF_GY_KALMAN 2000E-5F		// 2000E-5: th_e * th_e terms
#define FQWINITBB_6DOF_GY_KALMAN 250E-3F		// was 250E-4 for FXAS21000: b_e * b_e terms
#define FQWINITTHB_6DOF_GY_KALMAN 0.0F			// 0.0: th_e * b_e terms
#define FQWINITAA_6DOF_GY_KALMAN 10E-5F			// 10E-5: a_e * a_e terms (increase slows convergence to g but reduces sensitivity to shake)
// linear acceleration time constant
#define FCA_6DOF_GY_KALMAN 0.5F					// 0.1 linear acceleration decay factor

// *********************************************************************************
// COMPUTE_9DOF_GBY_KALMAN constants
// *********************************************************************************
// kalman filter noise variances
#define FQVA_9DOF_GBY_KALMAN 2E-6F				// 2E-6: accelerometer noise g^2 so 1.4mg RMS
#define FQVM_9DOF_GBY_KALMAN 0.1F				// 0.1: magnetometer noise uT^2
#define FQVG_9DOF_GBY_KALMAN 0.3F				// 0.3: gyro noise (deg/s)^2
#define FQWB_9DOF_GBY_KALMAN 1E-9F				// 1E-9: gyro offset drift (deg/s)^2: 1E-9 implies 0.09deg/s max at 50Hz
#define FQWA_9DOF_GBY_KALMAN 1E-4F				// 1E-4: linear acceleration drift g^2 (increase slows convergence to g but reduces sensitivity to shake)
#define FQWD_9DOF_GBY_KALMAN 0.5F				// 0.5: magnetic disturbance drift uT^2 (increase slows convergence to B but reduces sensitivity to magnet)
// initialization of Qw covariance matrix
#define FQWINITTHTH_9DOF_GBY_KALMAN 2000E-5F	// 2000E-5: th_e * th_e terms
#define FQWINITBB_9DOF_GBY_KALMAN 250E-3F		// was 250E-4 for FXAS21000: b_e * b_e terms
#define FQWINITTHB_9DOF_GBY_KALMAN 0.0F			// 0.0: th_e * b_e terms
#define FQWINITAA_9DOF_GBY_KALMAN 10E-5F		// 10E-5: a_e * a_e terms (increase slows convergence to g but reduces sensitivity to shake)
#define FQWINITDD_9DOF_GBY_KALMAN 600E-3F		// 600E-3: d_e * d_e terms (increase slows convergence to B but reduces sensitivity to magnet)
// linear acceleration and magnetic disturbance time constants
#define FCA_9DOF_GBY_KALMAN 0.5F				// 0.1 linear acceleration decay factor
#define FCD_9DOF_GBY_KALMAN 0.5F				// 0.1 magnetic disturbance decay factor
// maximum geomagnetic inclination angle tracked by Kalman filter
#define SINDELTAMAX 0.9063078F		// sin of max +ve geomagnetic inclination angle: here 65.0 deg
#define COSDELTAMAX 0.4226183F		// cos of max +ve geomagnetic inclination angle: here 65.0 deg

// *********************************************************************************
// Circuit Cellar globals
// *********************************************************************************
extern float PhVn, ThVn;
extern float Ph0, Th0;	
extern float wn[];
extern float aVn[];
extern struct fquaternion fqcc;
extern int32 systickcc;

// *********************************************************************************
// function prototypes
// *********************************************************************************
void fInit_1DOF_P_BASIC(struct SV_1DOF_P_BASIC *pthisSV, float flpftimesecs, int16 iSensorFS, int16 iOverSampleRatio);
void fInit_3DOF_G_BASIC(struct SV_3DOF_G_BASIC *pthisSV, float flpftimesecs, int16 iSensorFS, int16 iOverSampleRatio);
void fInit_3DOF_B_BASIC(struct SV_3DOF_B_BASIC *pthisSV, float flpftimesecs, int16 iSensorFS, int16 iOverSampleRatio);
void fInit_3DOF_Y_BASIC(struct SV_3DOF_Y_BASIC *pthisSV, int16 iSensorFS, int16 iOverSampleRatio);
void fInit_6DOF_GB_BASIC(struct SV_6DOF_GB_BASIC *pthisSV, float flpftimesecs, int16 iSensorFS, int16 iOverSampleRatio);
void fInit_6DOF_GB_KALMAN(struct SV_6DOF_GB_KALMAN *pthisSV, float flpftimesecs, int16 iSensorFS, int16 iOverSampleRatio);
void fInit_6DOF_GY_KALMAN(struct SV_6DOF_GY_KALMAN *pthisSV, int16 iSensorFS, int16 iOverSampleRatio);
void fInit_9DOF_GBY_KALMAN(struct SV_9DOF_GBY_KALMAN *pthisSV, int16 ithisCoordSystem, int16 iSensorFS, int16 iOverSampleRatio);

void fRun_1DOF_P_BASIC(struct SV_1DOF_P_BASIC *pthisSV, struct PressureSensor *pthisPressure, int32 loopcounter);
void fRun_3DOF_G_BASIC(struct SV_3DOF_G_BASIC *pthisSV, struct AccelSensor *pthisAccel, int32 loopcounter,
		int32 licenseword1, int32 licenseword2, int16 ithisCoordSystem);
void fRun_3DOF_B_BASIC(struct SV_3DOF_B_BASIC *pthisSV, struct MagSensor *pthisMag, int32 loopcounter,
		int32 licenseword1, int32 licenseword2, int16 ithisCoordSystem);
void fRun_3DOF_Y_BASIC(struct SV_3DOF_Y_BASIC *pthisSV, struct GyroSensor *pthisGyro, int32 loopcounter,
		int32 licenseword1, int32 licenseword2, int16 ithisCoordSystem, int16 iOverSampleRatio);
void fRun_6DOF_GB_BASIC(struct SV_6DOF_GB_BASIC *pthisSV, struct MagSensor *pthisMag, struct AccelSensor *pthisAccel, int32 loopcounter,
		int32 licenseword1, int32 licenseword2, int16 ithisCoordSystem);
void fRun_6DOF_GB_KALMAN(struct SV_6DOF_GB_KALMAN *pthisSV, struct MagSensor *pthisMag, struct AccelSensor *pthisAccel, 
		int32 licenseword1, int32 licenseword2, int16 ithisCoordSystem);
void Fusion(float Gn[], float Wn[]);
void fRun_6DOF_GY_KALMAN(struct SV_6DOF_GY_KALMAN *pthisSV, struct AccelSensor *pthisAccel, struct GyroSensor *pthisGyro,  
		int32 licenseword1, int32 licenseword2, int16 ithisCoordSystem, int16 iOverSampleRatio);
void fRun_9DOF_GBY_KALMAN(struct SV_9DOF_GBY_KALMAN *pthisSV, struct AccelSensor *pthisAccel, struct MagSensor *pthisMag, struct GyroSensor *pthisGyro,
		struct MagCalibration *pthisMagCal, int32 licenseword1, int32 licenseword2, int16 ithisCoordSystem, int16 iOverSampleRatio);

#endif   // #ifndef BARANSKI_KALMAN_H
