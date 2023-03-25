#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include <SPI.h>

Adafruit_MotorShield motorShield = Adafruit_MotorShield();
Adafruit_DCMotor leftMotor = Adafruit_DCMotor();
Adafruit_DCMotor rightMotor = Adafruit_DCMotor();



void setup() {
  // put your setup code here, to run once:


  
  motorShield.begin();
  leftMotor.setSpeed(150);
  rightMotor.setSpeed(150);
  

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  

  rightMotor.fullOn();
  leftMotor.fullOn();
  leftMotor.run(FORWARD);
  delay(1000);
  leftMotor.fullOff();
  rightMotor.run(FORWARD);
  delay(1000);
  rightMotor.fullOff();
}

void move(Adafruit_DCMotor motorName, Adafruit_DCMotor motorName2) {
  motorName.run(FORWARD);
  motorName.run(FORWARD);
}
