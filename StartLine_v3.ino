// MirroringSample - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers.  In this example, we're going to set up four NEOPIXEL strips on four
// different pins, and show the same thing on all four of them, a simple bouncing dot/cyclon type pattern

#include "FastLED.h"

#define NUM_LEDS 40
#define DATA_PIN 2
CRGB leds[NUM_LEDS];
int brightness = 82;

// For mirroring strips, all the "special" stuff happens just in setup.  We
// just addLeds multiple times, once for each strip
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // declare the ledPin as an OUTPUT
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  LEDS.setBrightness(brightness);
  // limit my draw to 1A at 5v of power draw
  FastLED.setMaxPowerInVoltsAndMilliamps(5,1000); 
  
  for(int i = 0; i < NUM_LEDS-1; i++) {
    // set all leds to red
    leds[i] = CRGB::Red;
    FastLED.show();
    delay(5);
  }
  
  // now bring in the orange from each end
  for(int i = 0; i < NUM_LEDS/2+2; i=i+2) {
    // set our current dot to orange
    leds[i] = CRGB::Orange;
    leds[i+1] = CRGB::Orange;
    leds[NUM_LEDS - i + 1] = CRGB::Orange;
    leds[NUM_LEDS - i] = CRGB::Orange;
    
    FastLED.show();
    // clear our current dot before we move on
    //leds[i+3] = CRGB::Purple;
    delay(500);
  }
  // Pause for effect
  delay(500);
    
   // now turn them all green
   for(int i = 0; i < NUM_LEDS; i++) {
    // set current dot to green
    leds[i] = CRGB::Green;
    FastLED.show();
  }
  
  delay(500);
}
