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
  // Assume that only one out of the two sensors in over the tape at any point
  if (isPortOverTape()) {
    portMotor->run(RELEASE);
    starboardMotor->run(FORWARD);
  }
  else if (isStarboardOverTape()) {
    starboardMotor->run(RELEASE);
    portMotor->run(FORWARD);
  } else if (!isOffCoursePort && !isOffCourseStarboard){
    portMotor->run(FORWARD);
    starboardMotor->run(FORWARD);
    // make sure both motors are going at same power
  }
}

/*Checks if the port sensor is over the tape.
If not, sets the offCourse flag to false. If off tape, sets the flag to true.
Returns isOffCoursePort*/
boolean isPortOverTape(){
  int portValue = analogRead(port);
  isOffCoursePort = portValue > 500;
  return isOffCoursePort;
}

boolean isStarboardOverTape(){
  int starboardValue = analogRead(starboard);
  isOffCourseStarboard = starboardValue > 500;
  return isOffCourseStarboard;
}

