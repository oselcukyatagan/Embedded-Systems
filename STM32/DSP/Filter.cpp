/*
 * Filter.cpp
 *
 *  Created on: Feb 19, 2025
 *      Author: omerselcuk
 */

 #include "Filter.h"

 // TODO Auto-generated constructor stub
 Filter::Filter(filterType type, float samplingFrequency, float cutoffFrequency){
 
     this->type = type;
     this->samplingFrequency = samplingFrequency;
     this->cutoffFrequency = cutoffFrequency;
     this->output = 0.0f;
 
     setCutoffFrequency(cutoffFrequency);
 
 }
 
 void Filter::setCutoffFrequency(float fc) {
     if (fc > samplingFrequency / 2.5f) fc = samplingFrequency / 2.5f;
     if (fc < 0.01f) fc = 0.01f;
 
     float alpha = (2 * M_PI * fc) / (samplingFrequency + (2 * M_PI * fc));
 
     coefficients[0] = alpha;
     coefficients[1] = 1.0f - alpha;
 }
 
 float Filter::applyLowPassFilter(float input){
 
     output = coefficients[0] * input + coefficients[1] * output;
     return output;
 }
 
 float Filter::applyHighPassFilter(float input){
 
     // TODO add high pass code.
 }
 
 
 Filter::~Filter() {
     // TODO Auto-generated destructor stub
 }
 
 