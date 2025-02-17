// Test code to intercept the transmit data with a logic analyser to see the uart protocol signals.

#include <SoftwareSerial.h>

#define _delay 1000

SoftwareSerial serialConnectionAudio(10,11); // Rx, Tx


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  serialConnectionAudio.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Serial connection is working.");
  serialConnectionAudio.println("Serial connection is working.");
  delay(_delay);
}
