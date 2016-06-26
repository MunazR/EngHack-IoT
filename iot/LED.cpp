#include <Arduino.h>
#include "LED.h"

int red_pin;
int green_pin;
int blue_pin;

LED::LED(int red, int green, int blue) {
  red_pin = red;
  green_pin = green;
  blue_pin = blue;

  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
}

void LED::rgb(int red, int green, int blue) {
  analogWrite(red_pin, red);
  analogWrite(green_pin, green);
  analogWrite(blue_pin, blue);  
}

