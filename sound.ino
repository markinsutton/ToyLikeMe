// Sound V1
#define buzzer 8
#include "pitches.h"


// notes in the melody:
int melody[] = {
  NOTE_C7, NOTE_C7, NOTE_C7, NOTE_C7, NOTE_D7, NOTE_C7, NOTE_D7, NOTE_E7
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 2
};

const int buttonPin = 7;   
const unsigned long durance = 1000;         // on time in milliseconds
unsigned long lastMillis;                   // stores the timestamp when the button gets pressed
bool isOn = false;                          // stores if the pixel is currently on (... if the effect runs)

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);   // if you don't have external resistors use the internal pullups with reversed logic
  pinMode(buzzer, OUTPUT);
}

void loop() {
    if (!digitalRead(buttonPin) && !isOn)         // check for button press to GND (inversed - therefore the !)
  {
    Serial.println(F("Switch on by button press"));
    isOn = true;   
    lastMillis = millis();

    }
    


  if (millis() - lastMillis >= durance && isOn ) // Check for time out
  {
    Serial.println(F("Switch off by time"));
    isOn = false;

        //VICTORY MELODY
    for (int thisNote = 0; thisNote < 8; thisNote++) {
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(8, melody[thisNote], noteDuration);
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
 
    }
    // stop the tone playing:
      noTone(8);
  }
  
  }
