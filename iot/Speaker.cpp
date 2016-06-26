#include <Arduino.h>
#include "Speaker.h"

int speaker_pin;

Speaker::Speaker(int pin) {
  speaker_pin = pin;
  pinMode(speaker_pin, OUTPUT);
}

void Speaker::beep(int delay_ms) {
  analogWrite(speaker_pin, 20);
  delay(delay_ms);
  analogWrite(speaker_pin, 0);
  delay(delay_ms);
}

