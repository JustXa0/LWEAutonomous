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
void turnRight(int degree);
void stop(AF_DCMotor motor);
void stop();



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

void loop() {
  readSensors();
  //Serial.println(sensorValues[1]);
  delay(20);

  if(((sensorValues[2] < 900) && (sensorValues[3] < 900))) {
    moveBackward();
  }
  else {
    moveForward();
    delay(200);
  }


  //moveForward();
  //turnRight(180);
  //turnLeft(180);
}

/*void readSensors() {
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
*/

void moveForward() {
  rightMotor.run(FORWARD);
  leftMotor.run(FORWARD);
}

void moveBackward() {
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