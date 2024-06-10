#include "phisick_control.ino"
#include "phone_control.h"

const int switchPin = 11; // pin where conected switch

void setup() {
  // pin modifying
  pinMode(switchPin, INPUT);
  
  // first initializateing
  Serial.begin(9600);
  
  // intializating phone control and phisic control
  physicalControlSetup();
  phoneControlSetup();
}

void loop() {
  
  // Check switch mode
  if (digitalRead(switchPin) == HIGH) {
    Serial.println("Physical Control Mode");
    physicalControlLoop();
  } else {
    Serial.println("Phone Control Mode");
    phoneControlLoop();
  }
}
