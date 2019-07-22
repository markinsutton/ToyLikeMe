int LED = 7; // Use the onboard Uno LED
int isObstaclePin = 2;  // This is our input pin
int isObstacle = HIGH;  // HIGH MEANS NO OBSTACLE

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


#include <FastLED.h>

//#define DEBUG
#define NUM_LEDS 30
#define DATA_PIN 7
#define COLOR_ORDER GRB
#define LED_TYPE    WS2812B
#define POT A0

// Define the array of leds
CRGB leds[NUM_LEDS];

int onePos = 2;
int twoPos = 2;
byte oneDir = 0;
byte twoDir = 0;





void setup() {
  pinMode(LED, OUTPUT);
  pinMode(isObstaclePin, INPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

#ifdef DEBUG
  Serial.begin(9600);
#endif

  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);

}

  

void loop() {
  isObstacle = digitalRead(isObstaclePin);
  if (isObstacle == LOW)
  {
    Serial.println("OBSTACLE!!, OBSTACLE!!");
    digitalWrite(LED, HIGH);

    //VICTORY MELODY
    // iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < 8; thisNote++) {

      // to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(8, melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(8);
    }
 

  // turn on the green and blue LEDs to draw the current
  // position of each line along the strip
  leds[onePos] = CRGB(0, 255, 0);
  leds[max(onePos - 1, 0)] = CRGB(0, 255, 0);
  leds[min(onePos + 1, NUM_LEDS - 1)] = CRGB(0, 255, 0);

  leds[twoPos] = CRGB(0, 0, 255);
  leds[max(twoPos - 1, 0)] = CRGB(0, 0, 255);
  leds[min(twoPos + 1, NUM_LEDS - 1)] = CRGB(0, 0, 255);

  FastLED.show();
  delay(150);

  // turn all LEDs off so they can be re-drawn on the next loop
  // in the next calculated position
  leds[onePos] = CRGB(0, 0, 0);
  leds[max(onePos - 1, 0)] = CRGB(0, 0, 0);
  leds[min(onePos + 1, NUM_LEDS - 1)] = CRGB(0, 0, 0);

  leds[twoPos] = CRGB(0, 0, 0);
  leds[max(twoPos - 1, 0)] = CRGB(0, 0, 0);
  leds[min(twoPos + 1, NUM_LEDS - 1)] = CRGB(0, 0, 0);

  FastLED.show();

#ifdef DEBUG
  Serial.print("One Direction: ");
  Serial.println(oneDir);
  Serial.print("One Position: ");
  Serial.println(onePos);
  //Serial.println();

  Serial.print("Two Direction: ");
  Serial.println(twoDir);
  Serial.print("Two Position: ");
  Serial.println(twoPos);
  Serial.println();
#endif

  // calculate the next position of each LED line by advancing the
  // LED position in the forward or reverse direction as required.
  // if the line reaches the end of the LED strip, it is time to
  // change its direction.
  if (oneDir == 0) {     // if going forward
    onePos += 4;
    if (onePos >= NUM_LEDS) {
      onePos = NUM_LEDS - 1;
      oneDir = 1;  // go in reverse direction
    }
  }
  // else {   //if going reverse
  if (oneDir == 1) {
    onePos -= 4;
    if (onePos <= 0) {
      onePos = 0;
      oneDir = 0;  // go in forward direction
    }
  }

  if (twoDir == 0) {     // if going forward
    twoPos += 3;
    if (twoPos >= NUM_LEDS) {
      twoPos = NUM_LEDS - 1;
      twoDir = 1;  // go in reverse direction
    }
  }
  //else {   //if going reverse
  if (twoDir == 1) {
    twoPos -= 3;
    if (twoPos <= 0) {
      twoPos = 0;
      twoDir = 0;  // go in forward direction
    }
  }


  }
  else
  {
    Serial.println("clear");
    digitalWrite(LED, LOW);
  }
  delay(200);
}
