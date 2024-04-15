#include <Servo.h>

Servo myservo;
const int buttonPin = 2;

bool canFeFiFoFum; // Boolean that assures players cannot activate the giant stomping early
bool isFlipped;

// state change
int buttonState = 0;
int prevButtonState = 0;

void setup() {
  myservo.attach(9); // Pin that servo is attached to
  pinMode(buttonPin, INPUT);

  isFlipped = false;
  canFeFiFoFum = false; // Starts false, make true when jack reaches the giant house
}

void loop() {
  //ActivateServo(myservo, buttonPin, 180);

  // State change detection
  buttonState = digitalRead(buttonPin);

  if (buttonState != prevButtonState) {
    if (buttonState == HIGH) {
      ActivateServo(myservo, buttonPin, 180);
    } else {
      //chill ig
    }
  }
  prevButtonState = buttonState;
}

// This method allows for any servo to be moved, passing any differences in the servos as parameters.
void ActivateServo(Servo servo, int inputPin, int angle) {
  if (!isFlipped) {
    servo.write(angle);
    isFlipped = true;
  } else if(isFlipped) {
    servo.write(0);
    isFlipped = false;
  }
}
