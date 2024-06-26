#ifndef PHISIC_CONTROL_H
#define PHISIC_CONTROL_H


#include "GyverLibs-master/GyverStepper/GyverStepper.h"
#include "Stepper-1.1.3/src/Stepper.h"


// Stepper motor definitions with steps per revolution and control pins
GStepper<STEPPER2WIRE> stepper1(800, 8, 9);   // Stepper motor 1, 800 steps/rev, controlled by pins 8 and 9
GStepper<STEPPER2WIRE> stepper2(800, 6, 7);   // Stepper motor 2, 800 steps/rev, controlled by pins 6 and 7
GStepper<STEPPER2WIRE> stepper3(800, 12, 13); // Stepper motor 3, 800 steps/rev, controlled by pins 12 and 13
GStepper<STEPPER2WIRE> stepperA(800, 2, 3);   // Stepper motor A, 800 steps/rev, controlled by pins 2 and 3
GStepper<STEPPER2WIRE> stepperB(800, 4, 5);   // Stepper motor B, 800 steps/rev, controlled by pins 4 and 5

// Define constants and variables
float K = 1000; // A constant used in calculations (not currently used in code)
int L;          // A general-purpose integer variable (not currently used in code)

int s3 = 0;  // A state variable for stepper 3 (not currently used in code)
int AL;      // A flag indicating the direction of stepper A
int BL;      // A flag indicating the direction of stepper B
int ereqL;   // A flag indicating the direction of stepper 3
int erkuL;   // A flag indicating the direction of stepper 2
int mekL;    // A flag indicating the direction of stepper 1
int zuygL;   // A variable indicating the state of inputs 30 and 31
int zuygE;   // A variable indicating if both inputs 30 and 31 are active

// Speed and acceleration settings for each stepper motor
int Av = 2000;  // Speed of stepper A in steps per second
int Aa = 1000;  // Acceleration of stepper A in steps per second squared
int Bv = 2000;  // Speed of stepper B in steps per second
int Ba = 1000;  // Acceleration of stepper B in steps per second squared
int ereqv = 2000;  // Speed of stepper 3 in steps per second
int ereqa = 800;   // Acceleration of stepper 3 in steps per second squared
int erkuv = 2000;  // Speed of stepper 2 in steps per second
int erkua = 800;   // Acceleration of stepper 2 in steps per second squared
int mekv = 2000;   // Speed of stepper 1 in steps per second
int meka = 800;    // Acceleration of stepper 1 in steps per second squared

const int returnToHomePin = 18; // Pin number for the return-to-home button

void physicalControlSetup() {
  // Initialize input pins with pull-up resistors
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  pinMode(28, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  pinMode(30, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);
  pinMode(35, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(returnToHomePin, INPUT_PULLUP); // Initialize the return-to-home button pin

  Serial.begin(9600);
  
  // Set initial speed and acceleration for each stepper motor
  stepper1.setRunMode(KEEP_SPEED); // speed control mode
  stepper1.setSpeed(mekv); 
  stepper1.setAcceleration(meka); // in degrees/sec

  stepper3.setRunMode(KEEP_SPEED); // speed control mode
  stepper3.setSpeed(ereqv); 
  stepper3.setAcceleration(ereqa); // in degrees/sec

  stepper2.setRunMode(KEEP_SPEED); // speed control mode
  stepper2.setSpeed(erkuv); 
  stepper2.setAcceleration(erkua); // in degrees/sec

  stepperA.setRunMode(KEEP_SPEED); // speed control mode
  stepperA.setSpeed(Av); 
  stepperA.setAcceleration(Aa); // in degrees/sec

  stepperB.setRunMode(KEEP_SPEED); // speed control mode
  stepperB.setSpeed(Bv); 
  stepperB.setAcceleration(Ba); // in degrees/sec
}

void physicalControlLoop() {
  // Check if the return-to-home button is pressed
  if (digitalRead(returnToHomePin)) {
    // Move all steppers to their initial positions
    stepper1.setRunMode(FOLLOW_POS);
    stepper1.setTarget(0);
    stepper1.tick();
    
    stepper2.setRunMode(FOLLOW_POS);
    stepper2.setTarget(0);
    stepper2.tick();
    
    stepper3.setRunMode(FOLLOW_POS);
    stepper3.setTarget(0);
    stepper3.tick();
    
    stepperA.setRunMode(FOLLOW_POS);
    stepperA.setTarget(0);
    stepperA.tick();
    
    stepperB.setRunMode(FOLLOW_POS);
    stepperB.setTarget(0);
    stepperB.tick();
  } else {
/////////////////////////////////////////////////////////////////////////
  // Check inputs from pins 30 and 31 to set zuygE and zuygL
  if ((digitalRead(30) && digitalRead(31))) {
    zuygE = 0;
  } else {
    if (!digitalRead(30) && digitalRead(31)) {
      zuygL = 0;
      zuygE = 1;
    }
    if (!digitalRead(31) && digitalRead(30)) {
      zuygL = 1;
      zuygE = 1;
    }
  }

  ///////////////////////////////////////////////////////////////////////////////
  // Control stepperA based on inputs from pins 26 and 27 and zuygE
  if ((digitalRead(26) && digitalRead(27)) && !zuygE) {
    stepperA.setRunMode(KEEP_SPEED);
    stepperA.setSpeed(Av);
    stepperA.setAcceleration(Aa);
  } else {
    if ((!digitalRead(26) && digitalRead(27)) || (zuygL && zuygE)) {
      if (AL == 0) {
        AL = 1;
        stepperA.reverse(AL);
      }
      stepperA.tick();
    }
    if ((!digitalRead(27) && digitalRead(26)) || (!zuygL && zuygE)) {
      if (AL == 1) {
        AL = 0;
        stepperA.reverse(AL);
      }
      stepperA.tick();
    }
  }
  //////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////
  // Control stepperB based on inputs from pins 28 and 29 and zuygE
  if ((digitalRead(28) && digitalRead(29)) && !zuygE) {
    stepperB.setRunMode(KEEP_SPEED);
    stepperB.setSpeed(Bv);
    stepperB.setAcceleration(Ba);
  } else {
    if ((!digitalRead(28) && digitalRead(29)) || (zuygL && zuygE)) {
      if (BL == 0) {
        BL = 1;
        stepperB.reverse(BL);
      }
      stepperB.tick();
    }
    if ((!digitalRead(29) && digitalRead(28)) || (!zuygL && zuygE)) {
      if (BL == 1) {
        BL = 0;
        stepperB.reverse(BL);
      }
      stepperB.tick();
    }
  }

  ///////////////////////////////////////////////////////////////////
  // Control stepper3 based on inputs from pins 32 and 33
  if (digitalRead(32) && digitalRead(33)) {
    stepper3.setRunMode(KEEP_SPEED);
    stepper3.setSpeed(ereqv);
    stepper3.setAcceleration(ereqa);
  } else {
    if (!digitalRead(32) && digitalRead(33)) {
      if (ereqL == 0) {
        ereqL = 1;
        stepper3.reverse(ereqL);
      }
      stepper3.tick();
    }
    if (!digitalRead(33) && digitalRead(32)) {
      if (ereqL == 1) {
        ereqL = 0;
        stepper3.reverse(ereqL);
      }
      stepper3.tick();
    }
  }
  //////////////////////////////////////////////////////////////////
  // Control stepper2 based on inputs from pins 22 and 23
  if (digitalRead(22) && digitalRead(23)) {
    stepper2.setRunMode(KEEP_SPEED);
    stepper2.setSpeed(erkuv);
    stepper2.setAcceleration(erkua);
  } else {
    if (!digitalRead(22) && digitalRead(23)) {
      if (erkuL == 0) {
        erkuL = 1;
        stepper2.reverse(erkuL);
      }
      stepper2.tick();
    }
    if (!digitalRead(23) && digitalRead(22)) {
      if (erkuL == 1) {
        erkuL = 0;
        stepper2.reverse(erkuL);
      }
      stepper2.tick();
    }
  }
  //////////////////////////////////////////////////////////////////
  // Control stepper1 based on inputs from pins 24 and 25
  if (digitalRead(24) && digitalRead(25)) {
    stepper1.setRunMode(KEEP_SPEED);
    stepper1.setSpeed(mekv);
    stepper1.setAcceleration(meka);
  } else {
    if (!digitalRead(24) && digitalRead(25)) {
      if (mekL == 0) {
        mekL = 1;
        stepper1.reverse(mekL);
      }
      stepper1.tick();
    }
    if (!digitalRead(25) && digitalRead(24)) {
      if (mekL == 1) {
        mekL = 0;
        stepper1.reverse(mekL);
      }
      stepper1.tick();
    }
  }
  ////////////////////////////////////////////////////////////////////
  }
}

#endif