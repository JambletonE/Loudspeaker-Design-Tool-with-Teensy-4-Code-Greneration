#include "mex.h"
#include <stdio.h>
#include <string.h>

void TDF2Filter(double B[], double A[], double x[], double zi[], double y[], double zf[] , size_t xLength, size_t ziLength){

    int i;
    double b0_over_a0 = B[0]/A[0]; //(b0 / a0) trying to speed up code
    double b1_over_a0 = B[1]/A[0]; //(b1 / a0)
    double a1_over_a0 = A[1]/A[0];
    double b2_over_a0 = B[2]/A[0];
    double a2_over_a0 = A[2]/A[0];

             for (i = 0; i < xLength; i++){
              
              y[i] = (b0_over_a0) * x[i] + zi[0]; //output
              zi[0] = (b1_over_a0) * x[i] + zi[1] - (a1_over_a0) * y[i]; //state 1
              zi[1] = (b2_over_a0) * x[i]  - (a2_over_a0) * y[i]; //state 2

            }
        

    memcpy(zf , zi , ziLength * sizeof(double));
    
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    

    double *B = mxGetPr(prhs[0]);
    double *A = mxGetPr(prhs[1]);
    double *x = mxGetPr(prhs[2]);
    double *zi = mxGetPr(prhs[3]);
    

    
    size_t xLength = mxGetNumberOfElements(prhs[2]);
    size_t ziLength = mxGetNumberOfElements(prhs[3]);
 
    
    double *y = mxGetPr(mxCreateDoubleMatrix(xLength, 1, mxREAL));
    double *zf = mxGetPr(mxCreateDoubleMatrix(ziLength, 1, mxREAL));

    
    TDF2Filter(B, A, x, zi, y, zf, xLength, ziLength);

    
    plhs[0] = mxCreateDoubleMatrix(xLength, 1, mxREAL);
    plhs[1] = mxCreateDoubleMatrix(ziLength , 1, mxREAL);
    
    
    memcpy(mxGetPr(plhs[0]), y, xLength * sizeof(double));
    memcpy(mxGetPr(plhs[1]), zf, ziLength * sizeof(double));
        
    

}


