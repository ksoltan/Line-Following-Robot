//Incorporate the motorshield and motors
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *portMotor = AFMS.getMotor(4);
Adafruit_DCMotor *starboardMotor = AFMS.getMotor(1);

//Create flags that are assigned when one of the IR sensors crosses the tape
boolean isOffCoursePort = false;
boolean isOffCourseStarboard = false;

//Assign pins to the two IR sensors
int port = A0;
int starboard = A1;
int v = 21;

void setup() {
  //Set up the motors and their speed
  AFMS.begin();
  portMotor->setSpeed(v);
  starboardMotor->setSpeed(v);
  Serial.begin(9600);
}

/*Checks if the port sensor is over the tape.
If not, sets the offCourse flag to false. If on tape, sets the flag to true.
Returns isOffCoursePort*/
boolean isPortOverTape(){
  int portValue = analogRead(port);
  isOffCoursePort = portValue > 325;
  return isOffCoursePort;
}

/*Checks if the starboard sensor is over the tape.
If not, sets the offCourse flag to false. If on tape, sets the flag to true.
Returns isOffCourseStarboard*/
boolean isStarboardOverTape(){
  int starboardValue = analogRead(starboard);
  isOffCourseStarboard = starboardValue > 500;
  return isOffCourseStarboard;
}

void logSensorValues(boolean portForward, boolean starboardForward){
  int portMotor = -v;
  int starboardMotor = -v;
  if(portForward){
    portMotor = v;
  }
  if(starboardForward){
    starboardMotor = v;
  }
  
  Serial.print(analogRead(port));
  Serial.print(",");
  Serial.print(analogRead(starboard));
  Serial.print(",");
  Serial.print(portMotor);
  Serial.print(",");
  Serial.println(starboardMotor);
}

void loop() {
  //logSensorValues(true, true);
// Instructions for the motors if the car is off course to the port side or starboard side, or if it is on course
// (assume that only one out of the two sensors is over the tape at any point)
    if (isPortOverTape()) {
      portMotor->run(BACKWARD);
      starboardMotor->run(FORWARD);
      logSensorValues(false, true);
    }
    else if (isStarboardOverTape()) {
      starboardMotor->run(BACKWARD);
      portMotor->run(FORWARD);
      logSensorValues(true, false);
    }
    else if (!isOffCoursePort && !isOffCourseStarboard){
      portMotor->run(FORWARD);
      starboardMotor->run(FORWARD);
      logSensorValues(true, true);
    }  
 }
