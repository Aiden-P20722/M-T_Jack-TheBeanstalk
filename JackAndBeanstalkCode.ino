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

const int ledPin=4;

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

  pinMode(ledPin,OUTPUT);

  isFlippedC = false;
  isFlippedH = false;
  isFlippedB = false;
  isFlippedG = false;

  canFeFiFoFum = false; // Starts false, make true when jack reaches the giant house

  Serial.begin(9600);
}

void loop() {
  // Read the value of the piezo sensor
  /*
  sensorVal=analogRead(sensorPin);
  Serial.println(sensorVal);
  if (sensorVal<=512){
    digitalWrite(ledPin,HIGH);
  }else{
    digitalWrite(ledPin,LOW);
  }
*/
  digitalWrite(ledPin,HIGH);
  
  if(digitalRead(jackButtonPin) == HIGH) {
    canFeFiFoFum = true;
  }
  //Checks every frame for the cow being placed on the switch
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
  
    } else {
      //chill ig
    }
  }
  


  // State change detection BEANSTALK
  
  //Serial.println(buttonStateB);
  if (buttonStateB != prevButtonStateB) {
    if (buttonStateB == HIGH) {
      if (isFlippedB) {
        beanstalkServo.write(0);
        isFlippedB = false;
      }
    } else {
      //chill ig
    }
  }


  // State change detection FAMILY
  
  //Serial.println(buttonStateH);
  if (buttonStateH != prevButtonStateH) {
    if (buttonStateH == HIGH) {
      // FOR GIANT DROP ActivateServo(myservo, buttonPin, 0, 90);
      if (!isFlippedB) {
        familyServo.write(180);
        isFlippedB = true;
      } else if(isFlippedB) {
        familyServo.write(0);
        isFlippedB = false;
      }
    } else {
      //chill ig
    }
  }


  // State change detection AXE
  //Serial.println(buttonStateA);
  if (buttonStateA != prevButtonStateA) {
    if (buttonStateA == HIGH) {
      // FOR GIANT DROP ActivateServo(myservo, buttonPin, 0, 90);
      if(!isFlippedB) {
        beanstalkServo.write(180);
        isFlippedB = true;
      }

      if (!isFlippedG) {
        giantServo.write(90);
        isFlippedG = true;
      } else if(isFlippedG) {
        giantServo.write(180);
        isFlippedG = false;
      }
    } else {
      //chill ig
    }
  }

  prevButtonStateC = buttonStateC;
  prevButtonStateB = buttonStateB;
  prevButtonStateH = buttonStateH;
  prevButtonStateA = buttonStateA;
}
