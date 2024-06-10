#ifndef PHONE_CONTROL_H
#define PHONE_CONTROL_H

#include "GyverLibs-master/GyverStepper/GyverStepper.h"
#include "Stepper-1.1.3/src/Stepper.h"


// SoftwareSerial BTSerial(10, 11); // RX, TX

// Stepper motor definitions with steps per revolution and control pins

void phoneControlSetup(){
    // // Set initial speed and acceleration for each stepper motor
    // stepper1.setRunMode(KEEP_SPEED); // speed control mode
    // stepper1.setSpeed(mekv); 
    // stepper1.setAcceleration(meka); // in degrees/sec

    // stepper3.setRunMode(KEEP_SPEED); // speed control mode
    // stepper3.setSpeed(ereqv); 
    // stepper3.setAcceleration(ereqa); // in degrees/sec

    // stepper2.setRunMode(KEEP_SPEED); // speed control mode
    // stepper2.setSpeed(erkuv); 
    // stepper2.setAcceleration(erkua); // in degrees/sec

    // stepperA.setRunMode(KEEP_SPEED); // speed control mode
    // stepperA.setSpeed(Av); 
    // stepperA.setAcceleration(Aa); // in degrees/sec

    // stepperB.setRunMode(KEEP_SPEED); // speed control mode
    // stepperB.setSpeed(Bv); 
    // stepperB.setAcceleration(Ba); // in degrees/sec

    // serial.begin(9600);
    // BTSerial.begin(9600);
    // Serial.println("Bluetooth module ready");
}


void phoneControlLoop()
{
    // string data[] = BTSerial.read();

    // // Check if phone send signal "return to home" program  go to home
    // if(data[0] == "return to home"){
    //     // Move all steppers to their initial positions
    //     stepper1.setRunMode(FOLLOW_POS);
    //     stepper1.setTarget(0);
    //     stepper1.tick();
        
    //     stepper2.setRunMode(FOLLOW_POS);
    //     stepper2.setTarget(0);
    //     stepper2.tick();
        
    //     stepper3.setRunMode(FOLLOW_POS);
    //     stepper3.setTarget(0);
    //     stepper3.tick();
        
    //     stepperA.setRunMode(FOLLOW_POS);
    //     stepperA.setTarget(0);
    //     stepperA.tick();
        
    //     stepperB.setRunMode(FOLLOW_POS);
    //     stepperB.setTarget(0);
    //     stepperB.tick();
    // } else {
    //     if (data[0] == "motor_1" && data[0] == "ach"){
            
    //     }
    // }
}

#endif