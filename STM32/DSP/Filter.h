/*
 * Filter.h
 *
 *  Created on: Feb 19, 2025
 *      Author: omerselcuk
 */

 #ifndef INC_CPPSRC_FILTER_H_
 #define INC_CPPSRC_FILTER_H_
 
 class Filter {
 public:
 
     enum filterType { highPassFilter, lowPassFilter };
 
     float samplingFrequency;
     float cutoffFrequency;
     float coefficients[2];
     float output;
 
     Filter(filterType type,float samplingFrequency, float cutoffFrequency);
 
     void setCutoffFrequency(float fc);
 
     float applyLowPassFilter(float input);
 
     float applyHighPassFilter(float input);
 
 
     virtual ~Filter();
 };
 