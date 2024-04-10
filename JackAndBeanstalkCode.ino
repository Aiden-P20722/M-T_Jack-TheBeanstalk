#include <Servo.h>

Servo myservo;
const int buttonPin = 2;

bool canFeFiFoFum; // Boolean that assures players cannot activate the giant stomping early
bool isFlipped;

void setup() {
  myservo.attach(9);
  pinMode(buttonPin, INPUT);

  isFlipped = false;
  canFeFiFoFum = false; // Starts false, make true when jack reaches the giant house
}

void loop() {
  ActivateServo(myservo, buttonPin, 180);
}

// This method allows for any servo to be moved, passing any differences in the servos as parameters.
void ActivateServo(Servo servo, int inputPin, int angle) {
  if (digitalRead(inputPin) == HIGH && !isFlipped) {
    servo.write(angle)
    isFlipped = true;
  } else {
    servo.write(0);
  }
}
