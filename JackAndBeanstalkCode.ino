#include <Servo.h>

Servo merchantServo;
Servo beanstalkServo;
Servo familyServo;
Servo giantServo;

const int cowButtonPin = 13;
const int harpButtonPin = 11;
const int beansButtonPin = 2;
const int jackButtonPin = 7;
const int axeButtonPin = 5;

bool canFeFiFoFum; // Boolean that assures players cannot activate the giant stomping early
bool isFlippedC; // cow
bool isFlippedH; // harp
bool isFlippedB; // beans
bool isFlippedG; // giant release
bool isFlippedJ; // jack in the giant's house
bool beanStalkUp;


// state change
int buttonStateC = 0;
int prevButtonStateC = 0;
// state change
int buttonStateH = 0;
int prevButtonStateH = 0;
// state change
int buttonStateB = 0;
int prevButtonStateB = 0;
// state change
int buttonStateJ = 0;
int prevButtonStateJ = 0;
// state change
int buttonStateA = 0;
int prevButtonStateA = 0;

// Used for piezo sensor
int sensorVal;
const int sensorPin=A0;

const int ledPinSlam = 4; // led indicating the table slam should be done
const int ledPinGiant = 8; // led revealing the giant's silhouette
const int ledPinHarp = 9; // led for golden shine on harp

void setup() {
  merchantServo.attach(12); // Pin that servo is attached to
  beanstalkServo.attach(3); // Pin that servo is attached to
  familyServo.attach(10); // Pin that servo is attached to
  giantServo.attach(6); // Pin that servo is attached to

  pinMode(cowButtonPin, INPUT);
  pinMode(harpButtonPin, INPUT);
  pinMode(beansButtonPin, INPUT);
  pinMode(jackButtonPin, INPUT);
  pinMode(axeButtonPin, INPUT);

  pinMode(ledPinSlam,OUTPUT);
  pinMode(ledPinGiant,OUTPUT);
  pinMode(ledPinHarp,OUTPUT);

  isFlippedC = false;
  isFlippedH = false;
  isFlippedB = true;
  isFlippedG = false;
  isFlippedJ = false;

  canFeFiFoFum = false; // Starts false, make true when jack reaches the giant house
  beanstalkServo.write(180);
  familyServo.write(180);
  merchantServo.write(0);
  giantServo.write(180);

  Serial.begin(9600);
}

void loop() {
  // Check if the table is slammed
  sensorVal = analogRead(sensorPin);


  if(canFeFiFoFum) {
    digitalWrite(ledPinSlam, HIGH);
    if(sensorVal != 0) {
      Serial.println(sensorVal);
    }
    if(sensorVal > 18 && !isFlippedG) {
      digitalWrite(ledPinGiant, HIGH);
    }
  }

  StateChangeDetect();
}

/*
// This method allows for any servo to be moved, passing any differences in the servos as parameters.
void ActivateServo(Servo servo, int goToAngle, int restAngle, bool isFlipped) {
  if (!isFlipped) {
    servo.write(goToAngle);
    isFlipped = true;
  } else if(isFlipped) {
    servo.write(restAngle);
    isFlipped = false;
  }
}
*/

//Servo myservo, int inputPin, int goToAngle, int restAngle, bool isFlipped
void StateChangeDetect() {
  // State change detection COW
  buttonStateC = digitalRead(cowButtonPin);
  buttonStateB = digitalRead(beansButtonPin);
  buttonStateH = digitalRead(harpButtonPin);
  buttonStateA = digitalRead(axeButtonPin);
  buttonStateJ = digitalRead(jackButtonPin);

  //Serial.println(buttonStateC);
  if (buttonStateC != prevButtonStateC) {
    if (buttonStateC == HIGH) {
      // FOR GIANT DROP ActivateServo(myservo, buttonPin, 0, 90);
      if (!isFlippedC) {
        merchantServo.write(180);
        isFlippedC = true;
      } else if(isFlippedC) {
        merchantServo.write(0);
        isFlippedC = false;
      }
  
    }
  }
  


  // State change detection BEANSTALK
  
  //Serial.println(buttonStateB);
  if (buttonStateB != prevButtonStateB) {
    if (buttonStateB == HIGH) {
      if (isFlippedB) {
        beanstalkServo.write(15);
        isFlippedB = false;
      }
    }
  }


  // State change detection FAMILY
  
  //Serial.println(buttonStateH);
  if (buttonStateH != prevButtonStateH) {
    if (buttonStateH == HIGH) {
      // FOR GIANT DROP ActivateServo(myservo, buttonPin, 0, 90);
      if (!isFlippedH) {
        familyServo.write(180);
        isFlippedH = true;
      } else if(isFlippedH) {
        familyServo.write(0);
        isFlippedH = false;
      }
    }
  }


  // State change detection AXE
  // Lowers the beanstalk, releases the fallen giant from behind the giant's house, and turns off the giant silhouette led.
  if (buttonStateA != prevButtonStateA) {
    if (buttonStateA == HIGH) {
      // FOR GIANT DROP ActivateServo(myservo, buttonPin, 0, 90);
      if(!isFlippedB) {
        beanstalkServo.write(180);
        isFlippedB = true;
      }

      digitalWrite(ledPinGiant, LOW);

      // Giant fall
      if (!isFlippedG) {
        giantServo.write(90);
        isFlippedG = true;
      } else if(isFlippedG) {
        giantServo.write(180);
        isFlippedG = false;
      }
    }
  }

  // Jack placed in the house lets the fefifofum pad activate
  if (buttonStateJ != prevButtonStateJ) {
    if (buttonStateJ == HIGH) {
      if(!isFlippedJ) {
        canFeFiFoFum = true;
      }
    }
  }

  prevButtonStateC = buttonStateC;
  prevButtonStateB = buttonStateB;
  prevButtonStateH = buttonStateH;
  prevButtonStateA = buttonStateA;
  prevButtonStateJ = buttonStateJ;
}
