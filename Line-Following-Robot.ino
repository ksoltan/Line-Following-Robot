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
  portMotor->setSpeed(17);
  starboardMotor->setSpeed(17);
  Serial.begin(9600);
}

void loop() {
  // Assume that only one out of the two sensors in over the tape at any point
  if (isPortOverTape()) {
    portMotor->run(BACKWARD);
    starboardMotor->run(FORWARD);
  }
  else if (isStarboardOverTape()) {
    starboardMotor->run(BACKWARD);
    portMotor->run(FORWARD);
  }
  else if (!isOffCoursePort && !isOffCourseStarboard){
    portMotor->run(FORWARD);
    starboardMotor->run(FORWARD);
    // make sure both motors are going at same power
  }
  else if (isOffCoursePort && isOffCourseStarboard){
    portMotor->run(FORWARD);
    starboardMotor->run(FORWARD);
    // if both sensors are on the tape, run it forward
  }
}
/*Checks if the port sensor is over the tape.
If not, sets the offCourse flag to false. If off tape, sets the flag to true.
Returns isOffCoursePort*/
boolean isPortOverTape(){
  int portValue = analogRead(port);
  isOffCoursePort = portValue > 300;
  return isOffCoursePort;
}

boolean isStarboardOverTape(){
  int starboardValue = analogRead(starboard);
  isOffCourseStarboard = starboardValue > 500;
  return isOffCourseStarboard;
}

