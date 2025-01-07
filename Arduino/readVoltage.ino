// C++ code
//

int inputPort = A2;
int redLed = 12;
int greenLed = 11;
int blueLed = 8;
int delayTime = 500;
int bitVoltage;
float realVoltage; 


void setup(){

  Serial.begin(9600);

}

void loop(){
	
  bitVoltage = analogRead(inputPort);
  realVoltage = (5./1023.) * bitVoltage;
  Serial.println(realVoltage);
  delay(delayTime);
  
  if(realVoltage < 2){
    digitalWrite(redLed,HIGH);
    digitalWrite(greenLed,LOW);
    digitalWrite(blueLed,LOW);
  }
  if(2 < realVoltage && realVoltage < 4){
    digitalWrite(redLed,LOW);
    digitalWrite(greenLed,HIGH);
    digitalWrite(blueLed,LOW);
  }
  if(4 < realVoltage){
    digitalWrite(redLed,LOW);
    digitalWrite(greenLed,LOW);
    digitalWrite(blueLed,HIGH);
  }



}
