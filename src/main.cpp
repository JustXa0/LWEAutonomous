#include <Arduino.h> // include the arduino library
#include <AFMotor.h> // include the motor shield library
#include <QTRSensors.h> // include the line sensor array library

#define WHEEL_DIAMETER 3.7
#define WHEEL_BASE 20



AFMotorController motorShield = AFMotorController(); // creates a motor controller object
AF_DCMotor leftMotor(3, MOTOR12_1KHZ); // creates a motor object with a 1KHZ PWM frequency
AF_DCMotor rightMotor(4, MOTOR12_1KHZ); // creates a motor object with a 1KHZ PWM frequency

QTRSensors qtr;
uint16_t sensorValues[6];

void readSensors();
void moveForward();
void moveBackward();
void turnLeft(int degree);
void turnLeft();
void turnRight(int degree);
void turnRight();
void stop(AF_DCMotor motor);
void stop();
boolean lineLeft;
boolean lineRight;
boolean lineCenter;



void setup() {
  // put your setup code here, to run once:
  
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5}, 6);
  motorShield.enable();
  leftMotor.setSpeed(255);
  rightMotor.setSpeed(255);
  Serial.begin(9600);
  delay(2000);
} 

void loop() 
{
  readSensors();
  //Serial.println(sensorValues[1]);


/*
  if ((sensorValues[0] > 900) && ((sensorValues[2] < 900) || (sensorValues[3] < 900)) && (sensorValues[5] > 900))
    moveForward();

  else if((sensorValues[0] < 940) && ((sensorValues[2] > 900) || (sensorValues[3] > 900)) && (sensorValues[5] > 900))
    turnLeft();

  else if((sensorValues[0] > 900) && ((sensorValues[2] > 900) || (sensorValues[3] > 900)) && (sensorValues[5] < 940))
    turnRight();
  
  else if((sensorValues[0] > 900) && (sensorValues[1] > 900) && (sensorValues[2] > 900) && (sensorValues[3] > 900) && (sensorValues[4] > 900) && (sensorValues[5] > 900))
    moveBackward();
*/

if(((sensorValues[2] + sensorValues[3]) / 2) < ((sensorValues[0] + sensorValues[5]) / 2)) {
  moveForward();
}
else if(((sensorValues[5] + sensorValues[4]) / 2 ) > ((sensorValues[0] + sensorValues[1]) / 2)) {
  turnLeft();
}
else if(((sensorValues[4] + sensorValues[5]) / 2) < ((sensorValues[0] + sensorValues[1]) / 2)) {
  turnRight();
}
else {
  moveBackward();
}

/* if(((sensorValues[2]+sensorValues[3])/2)-((sensorValues[0] -sensorValues[5])/2) <=- static_cast<uint16_t>(105)){
  moveForward();
}
  else if (((sensorValues[5] -sensorValues[4])/2)-((sensorValues[0]+sensorValues[1])/2) <= static_cast<uint16_t> (100)) {
    turnLeft();
  }
  else if (((sensorValues[4]+sensorValues[5])/2)-((sensorValues[0] -sensorValues[1])/2) <=- static_cast<uint16_t> (100)) {
    turnRight();
  }
  else {
    moveBackward();
  }
*/
/*
  if ((1000-(sensorValues[2]+sensoerValues[3])/2)-(1000-(sensorValues[0]- sensorValues[5])*1.5)>0)
	moveForward();
  */ 
}
void moveForward() 
{
  leftMotor.setSpeed(255);
  rightMotor.setSpeed(255);
  rightMotor.run(FORWARD);
  leftMotor.run(FORWARD);
}

void moveBackward() {
  leftMotor.setSpeed(255);
  rightMotor.setSpeed(255);
  rightMotor.run(BACKWARD);
  leftMotor.run(BACKWARD);
  }

void turnRight(int degree) {
  double distance = degree * (WHEEL_BASE / 2.0);
  double revolutions = distance / (WHEEL_DIAMETER * PI);
  for(double i = 0.0; i <= (revolutions * 255); i += .1) {
    rightMotor.run(FORWARD);
  }
  stop(rightMotor);
}

void turnLeft(int degree) {
  double distance = degree * (WHEEL_BASE / 2.0);
  double revolutions = distance / (WHEEL_DIAMETER * PI);
  for(double i = 0.0; i <= (revolutions * 255); i += .1) {
    leftMotor.run(FORWARD);
  }
  stop(leftMotor);
}

void readSensors() {
  qtr.read(sensorValues);
  for(uint8_t i = 0; i < 6; i++) {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();
}

void stop(AF_DCMotor motor) {
  motor.run(RELEASE);
}

void stop() {

  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
}

void turnLeft() {
  leftMotor.setSpeed(225);
  rightMotor.setSpeed(225);
  leftMotor.run(FORWARD);
  rightMotor.run(BACKWARD);
}

void turnRight() {
  leftMotor.setSpeed(225);
  rightMotor.setSpeed(225);
  rightMotor.run(FORWARD);
  leftMotor.run(BACKWARD);
}