#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *portMotor = AFMS.getMotor(4);
Adafruit_DCMotor *starboardMotor = AFMS.getMotor(1);


boolean isOffCoursePort = false;
boolean isOffCourseStarboard = false;
int port = A0;
int starboard = A1;

void setup() {
  AFMS.begin();
  portMotor->setSpeed(20);
  starboardMotor->setSpeed(20);
  Serial.begin(9600);
}

void loop() {
  int portValue = analogRead(port);
  int starboardValue = analogRead(starboard);
  if (isPortOverTape(portValue)) {
    portMotor->run(RELEASE);
    starboardMotor->run(FORWARD);
    //do something
  }
  if (isStarboardOverTape(starboardValue)) {
    starboardMotor->run(RELEASE);
    portMotor->run(FORWARD);
    //do the other thing
  }
  
  // If neither of the sensors are over tape,
  // continue straight and true
  if (!isOffCoursePort && !isOffCourseStarboard){
    portMotor->run(FORWARD);
    starboardMotor->run(FORWARD);
    // make sure both motors are going at same power
  }
}

boolean isPortOverTape(int sensorValue){
  boolean sensorOverTape = sensorValue > 500;
  if(sensorOverTape){
    isOffCoursePort = true;
  }else{
    isOffCoursePort = false;
  }
  return sensorOverTape;
}

boolean isStarboardOverTape(int sensorValue){
  boolean sensorOverTape = sensorValue > 500;
  if(sensorOverTape){
    isOffCourseStarboard = true;
  }else{
    isOffCourseStarboard = false;
  }
  return sensorOverTape;
}

