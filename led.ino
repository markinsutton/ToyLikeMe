
// ToyLikeMe Arch LED Sketch V1.0

#include <Adafruit_NeoPixel.h>


const int buttonPin = 7;                    // a button connected from this pin to GND
const int ledPin = 2;                       // the pin where the pixels are connected
const byte ledCount = 33;                   // How many NeoPixels are attached to the Arduino?
const unsigned long durance = 1500;         // on time in milliseconds
unsigned long lastMillis;                   // stores the timestamp when the button gets pressed
bool isOn = false;                          // stores if the pixel is currently on (... if the effect runs)

unsigned long lastUpdate = 0 ;        // for millis() when last update occurred
unsigned long patternInterval = 20 ;  // time between steps in the pattern


// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(ledCount, ledPin, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);   // if you don't have external resistors use the internal pullups with reversed logic
  strip.begin();                      // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();                       // Turn OFF all pixels ASAP
  strip.setBrightness(50);            // Set BRIGHTNESS to about 1/5 (max = 255)
  randomSeed(analogRead(0));          // recommended if you use random function
  Serial.begin(115200);               // for debug purposes we need the serial monitor
  Serial.println(F("wait for button press"));
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void theaterChaseRainbow() { // modified from Adafruit example to make it a state machine
  static int j = 0, q = 0;
  static boolean on = true;
  if (on) {
    for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
      strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
    }
  }
  else {
    for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
      strip.setPixelColor(i + q, 0);      //turn every third pixel off
    }
  }
  on = !on; // toggel pixelse on or off for next time
  strip.show(); // display
  q++; // update the q variable
  if (q >= 3 ) { // if it overflows reset it and update the J variable
    q = 0;
    j++;
    if (j >= 256) j = 0;
  }
  lastUpdate = millis(); // time for next change to the display
}
 
    
void goBlack()
{
  Serial.println(F("Switch off all pixels"));
  for (uint16_t i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(0,150,0));
  }
  strip.show();
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
    goBlack();
    isOn = false;
  }



   if(isOn &&(millis() - lastUpdate > patternInterval))  theaterChaseRainbow(); // calls pattern update if necessary
  

}
   
