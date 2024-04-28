#include <Servo.h>

Servo merchantServo;
Servo beanstalkServo;
Servo familyServo;
Servo giantServo;

//These are used for the copper tape switches, connected by BLUE wires.
const int cowButtonPin = 13;
const int harpButtonPin = 11;
const int beansButtonPin = 2;
const int jackButtonPin = 7;
const int axeButtonPin = 5;

//These bools make it so the switches stay in each position with a press and release, rather
//than returning to their default state when the switch is on LOW.
bool canFeFiFoFum; // Boolean that assures players cannot activate the giant stomping early. 
bool isFlippedC; // cow
bool isFlippedH; // harp
bool isFlippedB; // beans
bool isFlippedG; // giant release
bool isFlippedJ; // jack in the giant's house
bool beanStalkUp;


// state change COW
int buttonStateC = 0;
int prevButtonStateC = 0;
// state change HARP
int buttonStateH = 0;
int prevButtonStateH = 0;
// state change BEANS
int buttonStateB = 0;
int prevButtonStateB = 0;
// state change JACK
int buttonStateJ = 0;
int prevButtonStateJ = 0;
// state change AXE
int buttonStateA = 0;
int prevButtonStateA = 0;

// Used for piezo sensor
int sensorVal;
const int sensorPin=A0;

const int ledPinSlam = 4; // led indicating the table slam should be done, green on the right side of the enclosure.
const int ledPinGiant = 8; // led revealing the giant's silhouette, within the giant's house.
const int ledPinHarp = 9; // led for golden shine on harp, within the giant's house.

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

  //Sets all of the button bools to false as they have not been activated yet.
  isFlippedC = false;
  isFlippedH = false;
  isFlippedB = true;
  isFlippedG = false;
  isFlippedJ = false;

  canFeFiFoFum = false; // Starts false, make true when jack is placed on the switch in the giant's house.
  //These servo writes set the servos to the proper starting positions.
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

    if(sensorVal > 18 && !isFlippedG) {
      digitalWrite(ledPinGiant, HIGH);
    }
  }

  //Checks for copper tape switches being pressed every frame.
  StateChangeDetect();
}

void StateChangeDetect() {
  //Reads in the copper tape switch state
  buttonStateC = digitalRead(cowButtonPin);
  buttonStateB = digitalRead(beansButtonPin);
  buttonStateH = digitalRead(harpButtonPin);
  buttonStateA = digitalRead(axeButtonPin);
  buttonStateJ = digitalRead(jackButtonPin);

  // Flips the merchant when the cow is placed on the switch
  if (buttonStateC != prevButtonStateC) {
    if (buttonStateC == HIGH) {
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
  // Raises the beanstalk when the beans are placed on the switch
  if (buttonStateB != prevButtonStateB) {
    if (buttonStateB == HIGH) {
      if (isFlippedB) {
        beanstalkServo.write(15);
        isFlippedB = false;
      }
    }
  }


  // State change detection FAMILY
  // Flips the family and table in Jack's house when the harp is placed on the switch
  if (buttonStateH != prevButtonStateH) {
    if (buttonStateH == HIGH) {
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
  // Lowers the beanstalk, releases the fallen giant from behind the giant's house, and turns off the giant silhouette led
  // when jack is placed on the switch in the giant's house.
  if (buttonStateA != prevButtonStateA) {
    if (buttonStateA == HIGH) {
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
  //Sets the previous state to the current state
  prevButtonStateC = buttonStateC;
  prevButtonStateB = buttonStateB;
  prevButtonStateH = buttonStateH;
  prevButtonStateA = buttonStateA;
  prevButtonStateJ = buttonStateJ;
}
