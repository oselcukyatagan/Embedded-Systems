/*
 * lowPassFilter.h
 *
 *  Created on: Feb 16, 2025
 *      Author: omerselcuk
 */

 #ifndef SRC_LOWPASSFILTER_H_
 #define SRC_LOWPASSFILTER_H_
 
 
 typedef struct {
 
     float samplingFrequency;
 
     float coefficients[2];
 
     float output;
 
 } LowPassFilter;
 
 
 void initLowPassFilter(LowPassFilter* filter, float fs, float fc);
 
 void setCutoffFrequency(LowPassFilter* filter, float fc);
 
 float applyLowPassFilter(LowPassFilter* filter, float input);
 
 
 
 
 
 #endif /* SRC_LOWPASSFILTER_H_ */
 