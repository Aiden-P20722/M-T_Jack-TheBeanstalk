/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
*/

#include "pitches.h"

/* SILLY SLUGGERS
// notes in the melody:
int melody[] = {
  NOTE_D4, NOTE_B3, NOTE_D4, NOTE_B3, NOTE_D4, 0, NOTE_B3, NOTE_D4, NOTE_E4, NOTE_FS4, NOTE_FS4, NOTE_E4, NOTE_D4, NOTE_FS4, 0, 0, NOTE_D4, NOTE_E4, NOTE_FS4, NOTE_FS4, NOTE_E4, NOTE_D4, NOTE_F4, NOTE_E4, 0, NOTE_D4, 0, NOTE_D4, NOTE_E4, NOTE_B3, NOTE_A3, NOTE_D4, NOTE_B3, 0, NOTE_E4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 4, 8, 4, 8, 4, 4, 4, 4, 4, 8, 4, 2, 4, 8, 8, 8, 4, 4, 4, 4, 8, 8, 8, 4, 8, 8, 8, 4, 4, 8, 8, 8, 2
};
*/


int IHATEYOU[] = {
  NOTE_D4, NOTE_CON, NOTE_G4, NOTE_CON, 0, NOTE_D4, NOTE_C4, NOTE_G3
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int hateDurations[] = {
  4, 4, 4, 16, 8, 16, 16, 16
};
int hateNum = 8;
//--------------------------------------------------------------------
int R2[] = {
  NOTE_D6, NOTE_F6, NOTE_G5, NOTE_E6, NOTE_A6, NOTE_D6, NOTE_C6, NOTE_G6, NOTE_D2
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int r2Durations[] = {
  8, 8, 8, 8, 8, 8, 8, 8, 2
};
int r2Num = 9;
//-------------------------------------------------------------------------
int BESTIE[] = {
  NOTE_D5, NOTE_CON, 0, NOTE_CON, NOTE_G4
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int bestieDurations[] = {
  4, 4, 16, 16, 4
};
int bestieNum = 5;
//----------------------------------------------------------------------------
int UNEED2SHUTUP[] = {
  NOTE_F3, NOTE_D4, NOTE_G3, NOTE_E4, 0, NOTE_CON, NOTE_G3, NOTE_CON, NOTE_E4, NOTE_CON, 0, NOTE_F3
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int shutDurations[] = {
  16, 4, 16, 4, 8, 16, 4, 4, 4, 16, 8, 4
};
int shutNum = 12;
//--------------------------------------------------------------------------------------
int WOMP[] = {
  NOTE_B0, NOTE_C1, NOTE_CS1, NOTE_D2, NOTE_DS2, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_D4, NOTE_B0, NOTE_C1, NOTE_CS1, NOTE_D2, NOTE_DS2, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G2, NOTE_GS2, NOTE_A2, NOTE_G3
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int wompDurations[] = {
  64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 4, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 2
};
int wompNum = 24;
//--------------------------------------------------------------------
int MONEY[] = {
  NOTE_B0, NOTE_C1, NOTE_CS1, NOTE_D2, NOTE_DS2, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_D4, NOTE_B0, NOTE_C1, NOTE_CS1, NOTE_D2, NOTE_DS2, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G2, NOTE_GS2, NOTE_A2, NOTE_G3
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int moneyDurations[] = {
  64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 4, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 2
};
int moneyNum = 24;

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
int melodyNum = 8;

// constants won't change. They're used here to set pin numbers:
const int ledPin = 9;    // the number of the LED pin
int sensorVal;
const int sensorPin = A0;

int currentWord = 1; // used to cycle between the phrases
bool listening;

unsigned long currentTime;
unsigned long prevTime = 0;
int timerLength = 2000;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  listening = false;
  Serial.begin(9600);
}

void loop() {
  // read the state of the sensor value:
  sensorVal = analogRead(sensorPin);
  Serial.println(sensorVal);

  // check if the piezo was touched
  if (sensorVal > 1) {
    listening = true;
  } 
  if (sensorVal == 0 && listening == true) { // when piezo is released
    listening = false;
    // turn LED on:
    //digitalWrite(ledPin, HIGH);
    // talk
    
    if (currentWord == 1) {
      Speak(hateDurations, IHATEYOU, hateNum);
      currentWord = 2;
    } 
    else if (currentWord == 2) {
      Speak(r2Durations, R2, r2Num);
      currentWord = 3;
    } 
    else if (currentWord == 3) {
      Speak(bestieDurations, BESTIE, bestieNum);
      currentWord = 4;
    } 
    else if (currentWord == 4) {
      Speak(shutDurations, UNEED2SHUTUP, shutNum);
      currentWord = 5;
    }  
    else if (currentWord == 5) {
      Speak(wompDurations, WOMP, wompNum);
      currentWord = 6;
    } 
    else if (currentWord == 6) {
      Speak(noteDurations, melody, melodyNum);
      currentWord = 1;
    }
  }
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    // shut up
    noTone(4);
   // listening = false;
  }

  
}

//Method to make buzzer do the "words"
void Speak(int durations[], int notes[], int numNotes) {
    // iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < numNotes; thisNote++) {

      if (notes[thisNote] == 0 || notes[thisNote] == NOTE_CON){
        digitalWrite(ledPin, LOW);
      } else {
        digitalWrite(ledPin, HIGH);
      }
      // to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 800 / durations[thisNote];
      tone(4, notes[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(4);
    }
  }
