// #include <MultiStepper.hz

#include <AccelStepper.h>
#include <SoftwareSerial.h>

SoftwareSerial BTserial(4, 5); // Arduino(RX, TX) - HC-05 Bluetooth (TX, RX)

// CYAN
#define dirPin0 10
#define stepPin0 11

// MAGENTA
#define dirPin1 2
#define stepPin1 3

// YELLOW
#define dirPin2 6
#define stepPin2 7

// KEY
#define dirPin3 8
#define stepPin3 9

// STEPPER MOTORS (Type:driver, STEP, DIR)
AccelStepper cyanMotor(1, stepPin0, dirPin0);       // Stepper1   (C)
AccelStepper magentaMotor(1, stepPin1, dirPin1);    // Stepper2   (M)
AccelStepper yellowMotor(1, stepPin2, dirPin2);     // Stepper3   (Y)
AccelStepper keyMotor(1, stepPin3, dirPin3);        // Stepper4   (K)

int dataIn = 0, motorSpeed = 1500, maxMotorSpeed = 3000;
const int STEPS_PER_REV = 200;

boolean pressCan = false;
boolean cyanState = false, 
        magentaState = false, 
        yellowState = false,
        keyState = false;

void setup() {
  // start th serial communication with the host computer
  Serial.begin(9600);         // Default baud rate of Serial Terminal (for debugging purposes) 
  while (!Serial) Serial.print("Serial NOT initialized\n");
                              // wait for serial port to connect. Needed for native USB port only
  Serial.println("Arduino Serial initialized at 9600");

  // start communication with the HC-05 using 9600
  BTserial.begin(9600);       // Default baud rate of Bluetooth module
  while (!BTserial) Serial.print("BT 1 NOT initialized\n");
  Serial.print("BTserial initialized at 9600\n");
  
  // Set the maximum speed in steps per second:
  cyanMotor.setMaxSpeed(maxMotorSpeed);
  magentaMotor.setMaxSpeed(maxMotorSpeed);
  yellowMotor.setMaxSpeed(maxMotorSpeed);
  keyMotor.setMaxSpeed(maxMotorSpeed);

  // Set speed in steps per second
  cyanMotor.setSpeed(motorSpeed);
  magentaMotor.setSpeed(motorSpeed);
  yellowMotor.setSpeed(motorSpeed);
  keyMotor.setSpeed(motorSpeed);
  
  Serial.print("motor speed: ");
  Serial.print(motorSpeed);
  Serial.print(" | max motor speed: ");
  Serial.print(maxMotorSpeed);
  Serial.print("\n");
}

void loop() {
    dataIn = BTserial.read();

    if (dataIn == 0) {
      Serial.println("dataIn: ");
      Serial.println(dataIn);
      Serial.println("\n");
      pressCan = false;
      stopMotors();
    }
    
    if (dataIn == 1) {
      pressCan = true;
      Serial.println("dataIn: ");
      Serial.println(dataIn);
      Serial.println("\n");
      runCyanMotor();
    }
    if (dataIn == 2) {
      pressCan = true;
      Serial.println("dataIn: ");
      Serial.println(dataIn);
      Serial.println("\n");
      runMagentaMotor();
    }
    if (dataIn == 3) {        
      pressCan = true;
      Serial.println("dataIn: ");
      Serial.println(dataIn);
      Serial.println("\n");
      runYellowMotor();
    }
    if (dataIn == 4) {
      pressCan = true;
      Serial.println("dataIn: ");
      Serial.println(dataIn);
      Serial.println("\n");
      runKeyMotor();
    }
}

void runCyanMotor(){
  if(pressCan == true) {
    
      for(int i = 0; i < STEPS_PER_REV; i++){
        digitalWrite(stepPin0,HIGH); 
        delayMicroseconds(500); 
        digitalWrite(stepPin0,LOW); 
        delayMicroseconds(500);
      }
      cyanState = true;
      Serial.print("CYAN - active\n");
    
    pressCan = false;
  } 
}
  
void runMagentaMotor() {
  if(pressCan == true) {
      for(int i = 0; i < STEPS_PER_REV/2 * 2; i++){
        digitalWrite(stepPin1,HIGH); 
        delayMicroseconds(500); 
        digitalWrite(stepPin1,LOW); 
        delayMicroseconds(500);
      }
      magentaState = true;
      Serial.print("MAGENTA - active\n");
   
    pressCan = false;
  }
}

void runYellowMotor(){
  if(pressCan == true){
      for(int i = 0; i < STEPS_PER_REV; i++){
        digitalWrite(stepPin2,HIGH); 
        delayMicroseconds(500); 
        digitalWrite(stepPin2,LOW); 
        delayMicroseconds(500);
      }
      yellowState = true;
      Serial.print("YELLOW - active\n");
    
    pressCan = false;
  }
}

void runKeyMotor(){
  if(pressCan == true) {
      for(int i = 0; i < STEPS_PER_REV * 2; i++){
        digitalWrite(stepPin3,HIGH); 
        delayMicroseconds(500); 
        digitalWrite(stepPin3,LOW); 
        delayMicroseconds(500);
      }
      keyState = true;
      Serial.print("KEY - active\n");
    
    pressCan = false;
  } 
}

// If motors are down, they will be returned to initial position
void stopMotors() {
  if (cyanState == true) {
    pressCan = true;
    for(int i = 0; i < STEPS_PER_REV * 7; i++){
      digitalWrite(stepPin0,HIGH); 
      delayMicroseconds(500); 
      digitalWrite(stepPin0,LOW); 
      delayMicroseconds(500);
    }
    cyanState = false;
    Serial.print("CYAN - INACTIVE\n");
  }
  
  if (magentaState == true) {
    pressCan = true;
    for(int i = 0; i < STEPS_PER_REV * 7; i++){
      digitalWrite(stepPin1,HIGH); 
      delayMicroseconds(500); 
      digitalWrite(stepPin1,LOW); 
      delayMicroseconds(500);
    }
    magentaState = false;
    Serial.print("MAGENTA - INACTIVE\n");
  }
  
  if (yellowState == true) {
    pressCan = true;
    for(int i = 0; i < STEPS_PER_REV * 7; i++){
      digitalWrite(stepPin2,HIGH); 
      delayMicroseconds(500); 
      digitalWrite(stepPin2,LOW); 
      delayMicroseconds(500);
    }
    yellowState = false;
    Serial.print("YELLOW - INACTIVE\n");
  }
  
  if (keyState == true) {
    pressCan = true;
    for(int i = 0; i < STEPS_PER_REV * 3.5; i++){
      digitalWrite(stepPin3,HIGH); 
      delayMicroseconds(500); 
      digitalWrite(stepPin3,LOW); 
      delayMicroseconds(500);
    }
    keyState = false;
    Serial.print("KEY - INACTIVE\n");
  }
}
