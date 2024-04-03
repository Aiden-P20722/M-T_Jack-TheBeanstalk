#include <Servo.h>

Servo myservo;
const int buttonPin = 2;

bool isFlipped;

void setup() {
  myservo.attach(9);
  pinMode(buttonPin, INPUT);

  isFlipped = false;
}

void loop() {
  if (digitalRead(buttonPin) == HIGH && !isFlipped) {
    myservo.write(180)
    isFlipped = true;
  } else {
    myservo.write(0);
  }
}
