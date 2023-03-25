#include <Arduino.h>
#include <AFMotor.h>
#include <SPI.h>


AFMotorController motorShield = AFMotorController();
AF_DCMotor leftMotor(1, MOTOR12_2KHZ);
AF_DCMotor rightMotor(2, MOTOR12_2KHZ);



void setup() {
  // put your setup code here, to run once:
  motorShield.enable();
  leftMotor.setSpeed(255);
  rightMotor.setSpeed(255);
} 

void loop() {
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
  

}

void turnRight() {
  
}