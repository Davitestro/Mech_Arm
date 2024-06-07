#include <GyverStepper.h>

GStepper<STEPPER2WIRE> stepper1(800, 8, 9);
GStepper<STEPPER2WIRE> stepper2(800, 6, 7);
GStepper<STEPPER2WIRE> stepper3(800, 12, 13);

GStepper<STEPPER2WIRE> stepperA(800, 2, 3);
GStepper<STEPPER2WIRE> stepperB(800, 4, 5);

float K=1000; int L;

int s3=0; int AL; int BL; int ereqL; int erkuL; int mekL;int zuygL; int zuygE;

int Av=2000; int Aa=1000;
int Bv=2000; int Ba=1000;
int ereqv=2000;  int ereqa=800;
int erkuv=2000; int erkua=800;
int mekv=2000; int meka=800;



void setup() {

  pinMode(22,INPUT_PULLUP);
  pinMode(23,INPUT_PULLUP);
  pinMode(24,INPUT_PULLUP);
  pinMode(25,INPUT_PULLUP);
  pinMode(26,INPUT_PULLUP);
  pinMode(27,INPUT_PULLUP);
  pinMode(28,INPUT_PULLUP);
  pinMode(29,INPUT_PULLUP);
  pinMode(30,INPUT_PULLUP);
  pinMode(31,INPUT_PULLUP);
  pinMode(32,INPUT_PULLUP);
  pinMode(33,INPUT_PULLUP);
  pinMode(34,INPUT_PULLUP);
  pinMode(35,INPUT_PULLUP);
pinMode(LED_BUILTIN, OUTPUT);

  
  Serial.begin(9600);
  
  stepper1.setRunMode(KEEP_SPEED); // режим поддержания скорости
  stepper1.setSpeed(mekv); 
  stepper1. setAcceleration(meka);// в градусах/сек

  stepper3.setRunMode(KEEP_SPEED); // режим поддержания скорости
  stepper3.setSpeed(ereqv); 
  stepper3. setAcceleration(ereqa);// в градусах/сек


  stepper2.setRunMode(KEEP_SPEED); // режим поддержания скорости
  stepper2.setSpeed(erkuv); 
  stepper2. setAcceleration(erkua);// в градусах/сек

  stepperA.setRunMode(KEEP_SPEED); // режим поддержания скорости
  stepperA.setSpeed(Av); 
  stepperA. setAcceleration(Aa);// в градусах/сек 


  stepperB.setRunMode(KEEP_SPEED); // режим поддержания скорости
  stepperB.setSpeed(Bv); 
  stepperB. setAcceleration(Ba);// в градусах/сек
}
void loop() {

///////////////////////////////////////////////////////////////////////////
 if ((digitalRead(30)&& digitalRead(31))) {zuygE=0;} else
 {
    if (!digitalRead(30)&&digitalRead(31)){ zuygL==0;zuygE=1; }
    if (!digitalRead(31)&&digitalRead(30)){  zuygL==1;zuygE=1; }
    }

///////////////////////////////////////////////////////////////////////////

    
 ///////////////////////////////////////////////////////////////////////////////   
  if ((digitalRead(26)&& digitalRead(27)) && !zuygE ) 
   {stepperA.reset();  stepperA.setRunMode(KEEP_SPEED); 
    stepperA.setSpeed(Av); 
    stepperA. setAcceleration(Aa);} else

    {
    if ((!digitalRead(26)&&digitalRead(27))|| (zuygL && zuygE)){if (AL==0){AL=1;stepperA.reverse(AL);}stepperA.tick(); }
    if ((!digitalRead(27)&&digitalRead(26))|| (!zuygL && zuygE)){if (AL==1){AL=0;stepperA.reverse(AL);}stepperA.tick(); }
    }
//////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////
   if ((digitalRead(28)&& digitalRead(29)) && !zuygE ) 
   {stepperB.reset();  stepperB.setRunMode(KEEP_SPEED); 
    stepperB.setSpeed(Bv); 
    stepperB. setAcceleration(Ba);} else

    {
    if ((!digitalRead(28)&&digitalRead(29))||(zuygL && zuygE)){if (BL==0){BL=1;stepperB.reverse(BL);}stepperB.tick(); }
    if ((!digitalRead(29)&&digitalRead(28))||(!zuygL && zuygE)){if (BL==1){BL=0;stepperB.reverse(BL);}stepperB.tick(); }
    }

///////////////////////////////////////////////////////////////////

    if (digitalRead(32)&& digitalRead(33) ) 
   {stepper3.reset();  stepper3.setRunMode(KEEP_SPEED); 
    stepper3.setSpeed(ereqv); 
    stepper3. setAcceleration(ereqa);} else

    {
    if (!digitalRead(32)&&digitalRead(33)){if (ereqL==0){ereqL=1;stepper3.reverse(ereqL);}stepper3.tick(); }
    if (!digitalRead(33)&&digitalRead(32)){if (ereqL==1){ereqL=0;stepper3.reverse(ereqL);}stepper3.tick(); }
    }
//////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////

    if (digitalRead(22)&& digitalRead(23) ) 
   {stepper2.reset();  stepper2.setRunMode(KEEP_SPEED); 
    stepper2.setSpeed(erkuv); 
    stepper2. setAcceleration(erkua);} else

    {
    if (!digitalRead(22)&&digitalRead(23)){if (erkuL==0){erkuL=1;stepper2.reverse(erkuL);}stepper2.tick(); }
    if (!digitalRead(23)&&digitalRead(22)){if (erkuL==1){erkuL=0;stepper2.reverse(erkuL);}stepper2.tick(); }
    }
//////////////////////////////////////////////////////////////////////////


   ///////////////////////////////////////////////////////////////////

    if (digitalRead(24)&& digitalRead(25) ) 
   {stepper1.reset();  stepper1.setRunMode(KEEP_SPEED); 
    stepper1.setSpeed(mekv); 
    stepper1. setAcceleration(meka);} else

    {
    if (!digitalRead(24)&&digitalRead(25)){if (mekL==0){mekL=1;stepper1.reverse(mekL);}stepper1.tick(); }
    if (!digitalRead(25)&&digitalRead(24)){if (mekL==1){mekL=0;stepper1.reverse(mekL);}stepper1.tick(); }
    }
////////////////////////////////////////////////////////////////////////// 
  
}