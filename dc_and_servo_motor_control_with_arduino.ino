#include <Servo.h>

Servo myServo;

// Joystick pins
int joyX = A0;  
int joyY = A1;  

// DC Motor pins (L298N)
int motorEn = 3;  // Enable pin (PWM)
int motorIn1 = 5;
int motorIn2 = 6;

int xValue, yValue;

void setup() {
  Serial.begin(9600);
  myServo.attach(9);

  pinMode(motorEn, OUTPUT);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
}

void loop() {
  // Read joystick values
  xValue = analogRead(joyX); // X-axis for Servo
  yValue = analogRead(joyY); // Y-axis for DC Motor
  Serial.print("X: ");
  Serial.print(xValue);
 Serial.print("  Y: ");
 Serial.println(yValue);
  // ---- Servo Control (X-axis) ----
  if(yValue>520){
  int servoAngle = map(yValue, 520, 1023, 90, 180);
  myServo.write(servoAngle);
  delay(200);
  }
    if(yValue<480){
  int servoAngle = map(yValue, 0, 480, 0, 90);
  myServo.write(servoAngle);
  delay(200);
  }
  // ---- DC Motor Control (Y-axis) ----
  if (xValue > 530) {  
    // Forward
    Serial.println("Forward");
    digitalWrite(motorIn1, HIGH);
    digitalWrite(motorIn2, LOW);
    int speed = map(xValue, 530, 1023, 0, 255);
    analogWrite(motorEn, speed);
  }
  else if (xValue < 480) {
    // Backward
      Serial.println("Backward");
    digitalWrite(motorIn1, LOW);
    digitalWrite(motorIn2, HIGH);
    int speed = map(xValue, 470, 0, 0, 255);
    analogWrite(motorEn, speed);
  }
  else {
    // Stop
    digitalWrite(motorIn1, LOW);
    digitalWrite(motorIn2, LOW);
     myServo.write(90);
  }

  delay(20);
}
