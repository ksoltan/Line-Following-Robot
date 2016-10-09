#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *portMotor = AFMS.getMotor(1);
Adafruit_DCMotor *starboardMotor = AFMS.getMotor(4);


boolean isOffCoursePort = false;
boolean isOffCourseStarboard = false;

void setup() {
  AFMS.begin();
  portMotor->setSpeed(10);
  starboardMotor->setSpeed(10);
  Serial.begin(9600);
  int port = A0;
  int starboard = A1;
}

void loop() {
  int portValue = analogRead(port);
  int starboardValue = analogRead(starboard);
  if (isSensorOverTape(portValue)) {
    isOffCoursePort = true;
    portMotor->run(Release);
    //do something
  }
  if (isSensorOverTape(starboardValue)) {
    isOffCourseStarboard = true;
    starboardMotor->run(Release);
    //do the other thing
  }
  
  // If neither of the sensors are over tape,
  // continue straight and true
  if (!isOffCoursePort && !isOffCourseStarboard){
    portMotor->run(Forward);
    starboardMotor->run(Forward);
    // make sure both motors are going at same power
  }
}

boolean isSensorOverTape(int sensorValue){
  return false;
  // TODO
}
