#include "mex.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

void ohmsCalc(double f_out[], double fs, double r, double Zc, double Bl, double Sd, double ohms[], size_t fLength, double Rar[], double k[], double w[]){
   
    double pi = M_PI;
    int c = 343;
    int i;
    
    for (i = 0; i < fLength; i++){
        w[i] = 2 * pi * f_out[i] / fs;
        k[i]=w[i]/c;

        Rar[i]=Zc*(1.0/4.0)*((k[i]*r)*(k[i]*r));
        ohms[i] = ((Bl/Sd)*(Bl/Sd))*(1./Rar[i]);
        }

    
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    

    double *f_out = mxGetPr(prhs[0]);
    double fs = mxGetScalar(prhs[1]);
    double r = mxGetScalar(prhs[2]);
    double Zc = mxGetScalar(prhs[3]);
    double Bl = mxGetScalar(prhs[4]);
    double Sd = mxGetScalar(prhs[5]);

    
    size_t fLength = mxGetNumberOfElements(prhs[0]);
 
    
    
    double *ohms = mxGetPr(mxCreateDoubleMatrix(fLength, 1, mxREAL));
    double *w = mxGetPr(mxCreateDoubleMatrix(fLength, 1, mxREAL));
    double *k = mxGetPr(mxCreateDoubleMatrix(fLength, 1, mxREAL));
    double *Rar = mxGetPr(mxCreateDoubleMatrix(fLength, 1, mxREAL));


        
        
    ohmsCalc(f_out, fs, r, Zc, Bl, Sd, ohms, fLength, Rar, w, k);
    
    
    plhs[0] = mxCreateDoubleMatrix(fLength, 1, mxREAL);

    
    memcpy(mxGetPr(plhs[0]), ohms, fLength * sizeof(double));

        
    

}


