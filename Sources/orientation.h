#ifndef ORIENTATION_H
#define ORIENTATION_H
                     
// function prototypes
void f3DOFTiltNED(float fR[][3], float fGp[]);
void f3DOFTiltAndroid(float fR[][3], float fGp[]);
void f3DOFTiltWin8(float fR[][3], float fGp[]);
void f3DOFMagnetometerMatrixNED(float fR[][3], float fBc[]);
void f3DOFMagnetometerMatrixAndroid(float fR[][3], float fBc[]);
void f3DOFMagnetometerMatrixWin8(float fR[][3], float fBc[]);
void feCompassNED(float fR[][3], float *pfDelta, float fBc[], float fGp[]);
void feCompassAndroid(float fR[][3], float *pfDelta, float fBc[], float fGp[]);
void feCompassWin8(float fR[][3], float *pfDelta, float fBc[], float fGp[]);
void fNEDAnglesDegFromRotationMatrix(float R[][3], float *pfPhiDeg, float *pfTheDeg, float *pfPsiDeg,
		float *pfRhoDeg, float *pfChiDeg);
void fAndroidAnglesDegFromRotationMatrix(float R[][3], float *pfPhiDeg, float *pfTheDeg, float *pfPsiDeg,
		float *pfRhoDeg, float *pfChiDeg);
void fWin8AnglesDegFromRotationMatrix(float R[][3], float *pfPhiDeg, float *pfTheDeg, float *pfPsiDeg,
		float *pfRhoDeg, float *pfChiDeg);
void fRotationMatrixFromRotationVectorDeg(float R[][3], const float rvecdeg[], float fscaling);
void fQuaternionFromRotationVectorDeg(struct fquaternion *pq, const float rvecdeg[], float fscaling);
void fQuaternionFromRotationMatrix(float R[][3], struct fquaternion *pq);
void fRotationMatrixFromQuaternion(float R[][3], const struct fquaternion *pq);
void fRotationVectorDegFromRotationMatrix(float R[][3], float rvecdeg[]);
void fRotationVectorDegFromQuaternion(struct fquaternion *pq, float rvecdeg[]);
void fLPFOrientationMatrix(float fR[][3], float fLPR[][3], float flpf, float fdeltat, float fOmega[], int32 loopcounter);
void fLPFOrientationQuaternion(struct fquaternion *pfq, struct fquaternion *pfLPq, float flpf, float fdeltat, float fOmega[], int32 loopcounter);
void fLPFScalar(float *pfS, float *pfLPS, float flpf, int32 loopcounter);
struct fquaternion qAxB(const struct fquaternion *pqA, const struct fquaternion *pqB);
void qAeqBxC(struct fquaternion *pqA, const struct fquaternion *pqB, const struct fquaternion *pqC);
void qAeqAxB(struct fquaternion *pqA, const struct fquaternion *pqB);
struct fquaternion qconjgAxB(const struct fquaternion *pqA, const struct fquaternion *pqB);
void fqeqNormq(struct fquaternion *pq);
void fqAeq1(struct fquaternion *pqA);

#endif   // #ifndef ORIENTATION_H
