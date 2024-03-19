#include "mex.h"
#include <stdio.h>
#include <string.h>

void TDF2Filter(double B[], double A[], double x[], double zi[], double y[], size_t xLength, size_t ziLength, size_t ziHeight){

    int i, n, m;
  
    double *tempZi = (double*)malloc(ziHeight * ziLength * sizeof(double));
    memcpy(tempZi, zi, ziHeight * ziLength * sizeof(double));
    
    for (n = 0; n < ziHeight; n++){
        
        double d1=0;
            double d2= 0;

        
            for (i = 0; i < xLength; i++){
                
                y[i] = (B[0 + ziLength * n]/A[0]) * x[i] +d1;
            
                d1= (B[1 + ziLength *  n]/ A[0]) * x[i] - (A[1 + ziLength *  n]/A[0]) * y[i]  + d2; //
                
       
                d2 = (B[2 + ziLength *  n]/A[0]) * x[i]  - (A[2 + ziLength *  n]/A[0]) * y[i];
                
                x[i]=y[i];
                
            }
        
        
        
    }
    memcpy(zi,tempZi, ziHeight * ziLength * sizeof(double));
    
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    

    double *B = mxGetPr(prhs[0]);
    double *A = mxGetPr(prhs[1]);
    double *x = mxGetPr(prhs[2]);
    double *zi = mxGetPr(prhs[3]);
    

    
    size_t xLength = mxGetNumberOfElements(prhs[2]);

    
    
    size_t ziLength = mxGetN(prhs[3]);
    size_t ziHeight = mxGetM(prhs[3]);
    
    
    
    size_t B_Length = mxGetNumberOfElements(prhs[0]);
    
    
 
    
    double *y = mxGetPr(mxCreateDoubleMatrix(xLength, 1, mxREAL));
    double *zf = mxGetPr(mxCreateDoubleMatrix(ziHeight,ziLength, mxREAL));
    
    
   
    TDF2Filter(B, A, x, zi, y, xLength, ziLength, ziHeight);

    
   
    plhs[0] = mxCreateDoubleMatrix(xLength, 1, mxREAL);
    plhs[1] = mxCreateDoubleMatrix(ziHeight,ziLength, mxREAL);
    
    
    memcpy(mxGetPr(plhs[0]), y, xLength * sizeof(double));
   
    memcpy(mxGetPr(plhs[1]), zi,  ziLength * ziHeight * sizeof(double));
        
    

}


