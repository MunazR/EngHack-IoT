#include <Servo.h>
#include "System.h"
#include "Speaker.h"
#include "LED.h"
#include "Button.h"
#include "Relay.h"

Servo servo;
int servo_pos = 90;
int servo_state = 0;
int servo_delay = 0;

Speaker speaker(SPEAKER_PIN);
LED led(RED_LED_PIN, GREEN_LED_PIN, BLUE_LED_PIN);
Button button(BUTTON_PIN);
Relay relay(RELAY_PIN);

void setup() {
  Serial.begin(9600);
  
  led.rgb(255, 0, 0);
  speaker.beep(50);
  led.rgb(0, 255, 0);
  speaker.beep(50);
  led.rgb(0, 0, 255);
  speaker.beep(50);

  Serial.println("Setup complete");
}

void loop() {
  pollButton();
  updateServo();
  delay(10);
}

void updateServo() {
  if (servo_state == 0) {
    if (servo_pos < 90) {
      servo.write(++servo_pos);
    }
    else{
      servo.detach();  
    }
  }
  else if (servo_state == 1) {
    if (servo_pos > 0) {
      servo.write(--servo_pos);
    } 
    else {
      servo_state = 2;
      servo_delay = 0;
    }
  }
  else if (servo_state == 2) {
    if (servo_delay > 200) {
      servo_state = 3;
    } 
    else {
      servo_delay += 1;
    }
  }
  else if (servo_state == 3) {
    if (servo_pos < 90) {
      servo.write(++servo_pos);
    } 
    else {
      servo_state = 4;
      servo_delay = 0;
    }
  } 
  else if (servo_state == 4) {
    if (servo_delay > 200) {
      servo_state = 1;
    } 
    else {
      servo_delay += 1;
    }
  }
}

void pollButton() {
  if (button.pushed() == 1) {
    if (servo_state != 0) {
      led.rgb(255, 0, 0);
      speaker.beep(50);
      relay.disable();
      servo_state = 0;
    } 
    else {
      led.rgb(0, 255, 0);
      speaker.beep(50);
      servo.attach(SERVO_PIN);
      relay.enable();
      servo_state = 1;
    }

    while (button.pushed() == 1);
  }
}

