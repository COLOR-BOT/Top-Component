#include <SoftwareSerial.h>

// Include the AccelStepper library:
#include <AccelStepper.h>

SoftwareSerial BTserial(4, 5); // RX | TX


// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin0 8
#define stepPin0 9

#define dirPin1 6
#define stepPin1 7

#define dirPin2 2
#define stepPin2 3

#define dirPin3 10
#define stepPin3 11

#define motorInterfaceType 1

int prevState = -1;
int pressCan = -1;
int c = -1;

// Create 4 new instances of the AccelStepper class:
AccelStepper cyanMotor = AccelStepper(motorInterfaceType, stepPin0, dirPin0);
AccelStepper magentaMotor = AccelStepper(motorInterfaceType, stepPin1, dirPin1);
AccelStepper yellowMotor = AccelStepper(motorInterfaceType, stepPin2, dirPin2);
AccelStepper keyMotor = AccelStepper(motorInterfaceType, stepPin3, dirPin3);

void setup() {
  
  // start the serial communication with the host computer
  Serial.begin(9600);
  Serial.println("Arduino with HC-05 is ready");

  // start communication with the HC-05 using 9600 BR
  BTserial.begin(9600);  
  Serial.println("BTserial started at 9600");
  
  // Set the maximum speed in steps per second:
  cyanMotor.setMaxSpeed(500);
  magentaMotor.setMaxSpeed(500);
  yellowMotor.setMaxSpeed(500);
  keyMotor.setMaxSpeed(500);
}

void loop() {

  //Checks if the BT is available to be read/write
  if (BTserial.available())
    {   
        //Captures value from Mega and stores in c
        c = BTserial.read();
        Serial.write(c);

        //Based on value of 'c' targets specific motor
        //Values 1-4 presses a specific motor, O stops the last active motor
      switch(c){
  
       case 1: 
       if(prevState != c){
          prevState = c;
          pressCan = 1;
          CyanMotor();
       };
       
       case 2:
       if(prevState != c){
        pressCan = 1;
        prevState = c;
        MagentaMotor();
       };
       
       case 3:
       if(prevState != c){
        pressCan = 1;
        prevState = c;
        YellowMotor();
       };
       
       case 4:
       if(prevState != c){
        pressCan = 1;
        prevState = c;
        KeyMotor();
       };
       
       case 0:
        pressCan = 1;
        
        if(prevState != c){
          
           if(prevState== 1){
            CyanMotor();
           }
           if(prevState == 2){
            MagentaMotor();
           }
           if(prevState == 3){
            YellowMotor();
           }
           if(prevState == 4){
            KeyMotor();
           }
            prevState = c;
          
        };
       
       default:
       Serial.write("Oops something went wrong within the switch case!");
       break;
       
     }
    }

    //If bluetooth not available print error message
  else{
    Serial.write("Sorry, bluetooth not connected");
  }
    
}

//Presses the Cyan motor if press can = 1 
//Maintains press state until a zero is passed into the 'Switch Case' within main loop
void CyanMotor(){
  
  if(pressCan = 1){
    cyanMotor.setCurrentPosition(0);
  
    while(cyanMotor.currentPosition() != -1000)
    {
      cyanMotor.setSpeed(-600);
      cyanMotor.runSpeed();
    }
    pressCan*=-1;
  }
  
}

//Presses the Magenta motor if press can = 1 
//Maintains press state until a zero is passed into the 'Switch Case' within main loop
void MagentaMotor(){
  
  if(pressCan = 1){
    magentaMotor.setCurrentPosition(0);
  
    while(magentaMotor.currentPosition() != -1000)
    {
      magentaMotor.setSpeed(-600);
      magentaMotor.runSpeed();
    }
      pressCan*=-1;
  }
  
}

//Presses the Yellow motor if press can = 1 
//Maintains press state until a zero is passed into the 'Switch Case' within main loop
void YellowMotor(){
  
  if(pressCan = 1){
    yellowMotor.setCurrentPosition(0);
  
    while(yellowMotor.currentPosition() != -1000)
    {
      yellowMotor.setSpeed(-600);
      yellowMotor.runSpeed();
    }
        pressCan*=-1;
  }
  
}

//Presses the Key motor if press can = 1 
//Maintains press state until a zero is passed into the 'Switch Case' within main loop
void KeyMotor(){
  
  if(pressCan = 1){
    keyMotor.setCurrentPosition(0);
  
    while(keyMotor.currentPosition() != -1000)
    {
      keyMotor.setSpeed(-600);
      keyMotor.runSpeed();
    }
        pressCan*=-1;
  }
  
}
