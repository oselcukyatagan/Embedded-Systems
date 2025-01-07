// C++ code
//

#include <iostream>
#include <cstdint>

int inputPort = A2;
int redLed = 10;
int greenLed = 9;
int blueLed = 8;
int delayTime = 500;
int bitVoltage;
float realVoltage; 
float bitConverter = (5. / 1023.);
uint8_t ledBits = 0x07;


void setup(){

  Serial.begin(9600);
  DDRB |= 0x07;
  PORTB = 0x00;

}

void loop(){
	
  bitVoltage = analogRead(inputPort);
  realVoltage = bitConverter * bitVoltage;
  Serial.println(realVoltage);
  delay(delayTime);
  
  PORTB &= ~(0x07);

  if(realVoltage < 2){
    PORTB |= 0x04;
  }
  if(2 < realVoltage && realVoltage < 4){
    PORTB |= 0x02;
  }
  if(4 < realVoltage){
    PORTB |= 0x01;
  }

}
