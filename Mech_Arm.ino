const int switchPin = 11; // pin where connected
bool isSwitch = false;

void setup() {
  // pin modifying
  pinMode(switchPin, INPUT);
  
  // first initializing
  Serial.begin(9600);
  
  // initializing phone control and physical control
  physicalControlSetup();
  phoneControlSetup();
}

void loop() {
  // Check switch mode
  if (digitalRead(switchPin) == HIGH) {
    isSwitch = !isSwitch;
  }
  
  if (isSwitch) {
    Serial.println("Physical Control Mode");
    physicalControlLoop();
  } else {
    Serial.println("Phone Control Mode");
    phoneControlLoop();
  } 
}
