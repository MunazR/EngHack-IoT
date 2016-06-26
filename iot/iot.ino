#include <Servo.h>

const int LED_PIN = 13;
const int SERVO_PIN = 9;
const int BUTTON_PIN = 8;
const int SPEAKER_PIN = 6;
const int RED_LED_PIN = 12;
const int GREEN_LED_PIN = 11;
const int BLUE_LED_PIN = 10;

Servo servo;
int servo_pos = 90;
int servo_state = 0;
int servo_delay = 0;

void setup() {
  Serial.begin(9600);

  // Initialize LED outputs
  pinMode(LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

  // Initialize button input
  pinMode(BUTTON_PIN, INPUT);

  // Initialize servo
  servo.attach(SERVO_PIN);

  // Initialize speaker
  pinMode(SPEAKER_PIN, OUTPUT);
  
  
  rgbLED(255, 0, 0);
  beep(50);
  rgbLED(0, 255, 0);
  beep(50);
  rgbLED(0, 0, 255);
  beep(50);

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
      servo_pos += 1;
      servo.write(servo_pos);
    }
  }
  else if (servo_state == 1) {
    if (servo_pos > 0) {
      servo_pos -= 1;
      servo.write(servo_pos);
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
      servo_pos += 1;
      servo.write(servo_pos);
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
  if (digitalRead(BUTTON_PIN) == HIGH) {
    Serial.println("Button pushed");

    if (servo_state != 0) {
      Serial.println("Servo disabled");
      digitalWrite(LED_PIN, LOW);
      rgbLED(255, 0, 0);
      beep(50);
      servo_state = 0;
    } 
    else {
      Serial.println("Servo enabled");
      digitalWrite(LED_PIN, HIGH);
      rgbLED(0, 255, 0);
      beep(50);
      servo_state = 1;
    }

    while (digitalRead(BUTTON_PIN) == HIGH);
  }
}

void rgbLED(int red, int green, int blue) {
  analogWrite(RED_LED_PIN, red);
  analogWrite(GREEN_LED_PIN, green);
  analogWrite(BLUE_LED_PIN, blue);  
}

void beep(unsigned char delayms) {
  analogWrite(SPEAKER_PIN, 20);
  delay(delayms);
  analogWrite(SPEAKER_PIN, 0);
  delay(delayms);
}

