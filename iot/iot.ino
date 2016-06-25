#include <Servo.h>

int led = 13;

Servo servo;
int servoPos = 0;

void setup() {  
  // Initialize LED output
  pinMode(led, OUTPUT);
  
  servo.attach(9);
}

void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level) 
 
  for (servoPos = 0; servoPos < 90; servoPos += 1)
  {
    servo.write(servoPos);
    delay(10);  
  }
  
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  
  delay(2500);
 
  for (servoPos = 90; servoPos >= 1; servoPos -= 1)
  {
    servo.write(servoPos);
    delay(10);
  }
}
