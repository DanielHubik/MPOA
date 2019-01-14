#ifndef MATRIX_H
#define MATRIX_H

// function prototypes
void f3x3matrixAeqBxC(float A[][3], float B[][3], float C[][3]);
void f3x3matrixAeqI(float A[][3]);
void fmatrixAeqI(float *A[], int16 rc);
void f3x3matrixAeqScalar(float A[][3], float Scalar);
void f3x3matrixAeqBxTrC(float A[][3], float B[][3], float C[][3]);
void f3x3matrixAeqInvSymB(float A[][3], float B[][3]);
void f3x3matrixAeqAxScalar(float A[][3], float Scalar);
void f3x3matrixAeqMinusA(float A[][3]);
float f3x3matrixDetA(float A[][3]);
void eigencompute(float m[][10], float eigval[], float eigvec[][10], int8 n);
void fmatrixAeqInvA(float *A[], int8 iColInd[], int8 iRowInd[], int8 iPivot[], int8 isize);
void fmatrixAeqRenormRotA(float A[][3]);
void f3x3matrixAeqBxA(float A[][3], float B[][3]);

#endif   // #ifndef MATRIX_H
