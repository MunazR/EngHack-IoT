#include <Arduino.h>
#include "Relay.h"

int relay_pin;

Relay::Relay(int pin) {
  relay_pin = pin;

  pinMode(relay_pin, OUTPUT);
}

void Relay::enable() {
  digitalWrite(relay_pin, HIGH);  
}

void Relay::disable() {
  digitalWrite(relay_pin, LOW);  
}

