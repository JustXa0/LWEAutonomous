#include <Arduino.h>
#include <AFMotor.h>
#include <QTRSensors.h>
#include <SPI.h>


AFMotorController motorShield = AFMotorController();
AF_DCMotor leftMotor(1, MOTOR12_2KHZ);
AF_DCMotor rightMotor(2, MOTOR12_2KHZ);

QTRSensors qtr;

void readSensors();
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();




void setup() {
  // put your setup code here, to run once:
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5}, 6);
  motorShield.enable();
  leftMotor.setSpeed(255);
  rightMotor.setSpeed(255);
} 

void loop() {
  //readSensors();

  moveForward();
}

void readSensors() {
  uint16_t sensors[6];
  uint16_t position = qtr.readLineWhite(sensors);

  if((sensors[0] > 750) && (sensors[1] > 750) && (sensors[2] > 750) && (sensors[3] > 750) && (sensors[4] > 750) && (sensors[5] > 750)) {
    moveBackward();
  }

  int16_t error = position - 1000;

  if(error < -500) {
    turnLeft();
  }
  else if(error > 500) {
    turnRight();
  }
  else {
    moveForward();
  }

}

void moveForward() {
  rightMotor.run(FORWARD);
  leftMotor.run(FORWARD);
}

void moveBackward() {
  rightMotor.run(BACKWARD);
  leftMotor.run(BACKWARD);
  }

void turnRight() {
  for(int i = 0; i < 250; i++) {
    rightMotor.run(BACKWARD);
    leftMotor.run(FORWARD);
  }
}
  void turnLeft() {
    for(int i = 0; i < 250; i++) {
      rightMotor.run(FORWARD);
      leftMotor.run(BACKWARD);
    }
}
