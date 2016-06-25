#include <Servo.h>
#include <IRremote.h>
#include <Timer.h>

int led_pin = 13;
int servo_pin = 9;
int ir_pin = 10;

Servo servo;
int servo_pos = 0;
int servo_state = 0;
int servo_delay = 0;

IRrecv irrecv(ir_pin);
decode_results ir_results;

void setup() {
  Serial.begin(9600);

  // Initialize LED output
  pinMode(led_pin, OUTPUT);

  // Initialize servo
  servo.attach(servo_pin);

  // Initialize IR
  irrecv.enableIRIn();

  Serial.println("Setup complete");
}

void loop() {
  pollButton();
  //updateServo();
  delay(10);
}

void updateServo() {
  if (servo_state == 0) {
    if (servo_pos >= 0) {
      servo_pos -= 1;
      servo.write(servo_pos);
    }
  }
  else if (servo_state == 1) {
    if (servo_pos <= 90) {
      servo_pos += 1;
      servo.write(servo_pos);
    } 
    else {
      servo_state = 2;
      servo_delay = 0;
    }
  }
  else if (servo_state == 2) {
    if (servo_delay >= 200) {
      servo_state = 3;
    } 
    else {
      servo_delay += 1;
    }
  }
  else if (servo_state == 3) {
    if (servo_pos >= 0) {
      servo_pos -= 1;
      servo.write(servo_pos);
    } 
    else {
      servo_state = 1;
    }
  }
}

void pollButton() {
  if (irrecv.decode(&ir_results)) {
    int ir_response = translateIR();
    Serial.println("Received IR response" + ir_response);

    if (ir_response == 1) {
      Serial.println("Servo enabled");
      digitalWrite(led_pin, HIGH);
      servo_state = 1;
    } 
    else if (ir_response == 2) {
      Serial.println("Servo disabled");
      digitalWrite(led_pin, LOW);
      servo_state = 0;
    }

    irrecv.resume(); // Receive the next value
  }
}

int translateIR() {
  switch(ir_results.value) 
  {
  case 0xFF30CF:  
    return 1;
  case 0xFF18E7:  
    return 2;
  case 0xFF7A85:  
    return 3;
  case 0xFF10EF:  
    return 4;
  case 0xFF38C7:  
    return 5;
  case 0xFF5AA5:  
    return 6;
  case 0xFF42BD:  
    return 7;
  case 0xFF4AB5:  
    return 8;
  case 0xFF52AD:  
    return 9;
  default: 
    return -1;
  }
} 








