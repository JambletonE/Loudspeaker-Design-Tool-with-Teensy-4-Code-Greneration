#include "mex.h"
#include <stdio.h>
#include <string.h>

void TDF2Filter(double B[], double A[], double x[], double zi[], double y[], double zf[] , size_t xLength, size_t ziLength, size_t B_Length){


    double b0_over_a0 = B[0]/A[0]; //(b0 / a0) trying to speed up code
    double b1_over_a0 = B[1]/A[0]; //(b1 / a0)
    double a1_over_a0 = A[1]/A[0];
    
    int i;
    

    if (B_Length == 3){

        double b2_over_a0 = B[2]/A[0];
        double a2_over_a0 = A[2]/A[0];

             for (i = 0; i < xLength; i++){
              
              y[i] = (b0_over_a0) * x[i] + zi[0]; //output
              zi[0] = (b1_over_a0) * x[i] + zi[1] - (a1_over_a0) * y[i]; //state 1
              zi[1] = (b2_over_a0) * x[i]  - (a2_over_a0) * y[i]; //state 2

            }
        }

    else if (B_Length == 5){
  

        
        double b2_over_a0 = B[2]/A[0];
        double a2_over_a0 = A[2]/A[0];
        double a3_over_a0 = A[3]/A[0];
        double a4_over_a0 = A[4]/A[0];
        double b3_over_a0 = B[3]/A[0];
        double b4_over_a0 = B[4]/A[0];
  
            for (i = 0; i < xLength; i++){
      
                y[i] = (b0_over_a0) * x[i] + zi[0]; //output
                zi[0] = (b1_over_a0) * x[i] + zi[1] - (a1_over_a0) * y[i]; //state 1
                zi[1] = (b2_over_a0) * x[i]  + zi[2] - (a2_over_a0) * y[i]; //state2
                zi[2] = (b3_over_a0) * x[i] + zi[3] - (a3_over_a0) * y[i]; //state 3
                zi[3] = (b4_over_a0) * x[i]  - (a4_over_a0) * y[i]; //state 4
                }
        }

        else{

           

            for (i = 0; i < xLength; i++){
        
                y[i] = (b0_over_a0) * x[i] + zi[0]; //output
                zi[0] = (b1_over_a0) * x[i] + zi[1] - (a1_over_a0) * y[i]; //state 1
        

                }
    
    
            }
    memcpy(zf,zi, ziLength * sizeof(double));
    }

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {


    double *B = mxGetPr(prhs[0]);
    double *A = mxGetPr(prhs[1]);
    double *x = mxGetPr(prhs[2]);
    double *zi = mxGetPr(prhs[3]);
    
 
    
    size_t xLength = mxGetNumberOfElements(prhs[2]);
    size_t ziLength = mxGetNumberOfElements(prhs[3]);
    size_t B_Length = mxGetNumberOfElements(prhs[0]);
    
    double *y = mxGetPr(mxCreateDoubleMatrix(xLength, 1, mxREAL));
    double *zf = mxGetPr(mxCreateDoubleMatrix(ziLength, 1, mxREAL));

    
    TDF2Filter(B, A, x, zi, y, zf, xLength, ziLength, B_Length);

    
    plhs[0] = mxCreateDoubleMatrix(xLength, 1, mxREAL);
    plhs[1] = mxCreateDoubleMatrix(ziLength , 1, mxREAL);
    
    
    memcpy(mxGetPr(plhs[0]), y, xLength * sizeof(double));
    memcpy(mxGetPr(plhs[1]), zf, ziLength * sizeof(double));
        
    

}


