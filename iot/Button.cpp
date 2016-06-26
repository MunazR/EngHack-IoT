#include <Arduino.h>
#include "Button.h"

int button_pin;

Button::Button(int pin) {
  button_pin = pin;
  
  pinMode(button_pin, INPUT);
}

int Button::pushed() {
  if (digitalRead(button_pin) == HIGH) {
    return 1;
  }
  return -1;
}

