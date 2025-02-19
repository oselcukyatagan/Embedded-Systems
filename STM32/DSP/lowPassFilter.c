/*
 * lowPassFilter.c
 *
 *  Created on: Feb 16, 2025
 *      Author: omerselcuk
 */


 #include "lowPassFilter.h"
 #include <Math.h>
 
 
 /*
  *
  * Low pass filter theory,
  *
  * H(s) = 1/(1+sRC) ->  Vo(1+sRC)= Vin -> Vo + Vo(sRC) = Vin -> Inverse Laplace, Vo(t)+ dVo/dt * (RC) = Vin(t)
  *
  * Discrete time derivative, X[n] - X[n-1] / T.
  *
  * Vo[n] + (Vo[n] - Vo[n-1] / T) * RC = Vin(t) -> (1 + (RC / T)Vo[n] - (RC/T)Vo[n-1] =  Vin[n] -> Vo[n] = Vin(T/(1+RC)) + Vo[n-1](RC/T)(1+(RC/T))
  *
  * Vo[n] = alpha * Vi[n] + (1-alpha)Vo[n-1]. Where alpha = T/(RC+T)
  *
  *
  */
 
 void initLowPassFilter(LowPassFilter* filter, float Fc,float Fs){
 
     filter->samplingFrequency = Fs;
     setCutoffFrequency(filter, Fc);
 
     filter->output = 0;
 
 }
 
 
 void setCutoffFrequency(LowPassFilter* filter, float Fc){
 
     if(Fc > filter->samplingFrequency / 2.0) Fc = filter->samplingFrequency/2.0;
     else if (Fc < 0.1f) Fc = 0.1f;
 
     float alpha = (2 * M_PI * Fc) / (filter->samplingFrequency + (2 * M_PI * Fc));
 
     filter->coefficients[0] = alpha;
     filter->coefficients[1] = 1 - alpha;
 
 }
 
 
 float applyLowPassFilter(LowPassFilter* filter, float input){
 
     filter->output = filter->coefficients[0] * input + filter->coefficients[1] * filter->output;
 
     return filter->output;
 
 }
 
 
 
