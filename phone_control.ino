#ifndef PHISIC_CONTROL_H
#define PHISIC_CONTROL_H

#include <GyverStepper.h>
#include <Stepper.h>


SoftwareSerial BTSerial(10, 11); // RX, TX

// Stepper motor definitions with steps per revolution and control pins
GStepper<STEPPER2WIRE> stepper1(800, 8, 9);   // Stepper motor 1, 800 steps/rev, controlled by pins 8 and 9
GStepper<STEPPER2WIRE> stepper2(800, 6, 7);   // Stepper motor 2, 800 steps/rev, controlled by pins 6 and 7
GStepper<STEPPER2WIRE> stepper3(800, 12, 13); // Stepper motor 3, 800 steps/rev, controlled by pins 12 and 13
GStepper<STEPPER2WIRE> stepperA(800, 2, 3);   // Stepper motor A, 800 steps/rev, controlled by pins 2 and 3
GStepper<STEPPER2WIRE> stepperB(800, 4, 5);   // Stepper motor B, 800 steps/rev, controlled by pins 4 and 5

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

void phoneControlSetup(){
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

    serial.begin(9600);
    BTSerial.begin(9600);
    Serial.println("Bluetooth module ready");
}


void phoneControlLoop()
{
    string data[] = BTSerial.read();

    // Check if phone send signal "return to home" program  go to home
    if(data[0] == "return to home"){
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
        if (data[0] == "motor_1" && data[0] == "ach"){
            
        }
    }
}

#endif