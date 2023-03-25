#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include <SPI.h>


Adafruit_MotorShield motorShield = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = motorShield.getMotor(1);
Adafruit_DCMotor *rightMotor = motorShield.getMotor(2);



void setup() {
  // put your setup code here, to run once:
  
  motorShield.begin();
  leftMotor->setSpeed(150);
  rightMotor->setSpeed(150);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  leftMotor->run(FORWARD);
  delay(1000);
  leftMotor->run(RELEASE);
  rightMotor->run(FORWARD);
  delay(1000);
  rightMotor->run(RELEASE);
}

void move(Adafruit_DCMotor motorName, Adafruit_DCMotor motorName2) {
  motorName.run(FORWARD);
  motorName.run(FORWARD);

}
