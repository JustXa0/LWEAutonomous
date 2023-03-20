#include <Arduino.h>

/*
   sensor array:
   A0 thru A5 - sensors 2 thru 6
   

*/

void setup() {
  // put your setup code here, to run once:

  // initialzes all analog pins for input
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  pinMode(LED_BULITIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}