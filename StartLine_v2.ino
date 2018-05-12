// MirroringSample - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers.  In this example, we're going to set up four NEOPIXEL strips on four
// different pins, and show the same thing on all four of them, a simple bouncing dot/cyclon type pattern

#include "FastLED.h"

#define NUM_LEDS_PER_STRIP 31
CRGB leds[NUM_LEDS_PER_STRIP];

// For mirroring strips, all the "special" stuff happens just in setup.  We
// just addLeds multiple times, once for each strip
void setup() {
  // tell FastLED there's 60 NEOPIXEL leds on pin 4
  FastLED.addLeds<NEOPIXEL, 3>(leds, NUM_LEDS_PER_STRIP);

  // tell FastLED there's 60 NEOPIXEL leds on pin 5
  //FastLED.addLeds<NEOPIXEL, 5>(leds, NUM_LEDS_PER_STRIP);

  // tell FastLED there's 60 NEOPIXEL leds on pin 6
  //FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS_PER_STRIP);

  // tell FastLED there's 60 NEOPIXEL leds on pin 7
  //FastLED.addLeds<NEOPIXEL, 7>(leds, NUM_LEDS_PER_STRIP);
}

void loop() {
  for(int i = 0; i < NUM_LEDS_PER_STRIP-1; i++) {
    // set all leds to red
    leds[i] = CRGB::Red;
    FastLED.show();
    delay(5);
  }
  
  // now bring in the orange from each end
  for(int i = 0; i < NUM_LEDS_PER_STRIP/2+2; i=i+2) {
    // set our current dot to orange
    leds[i] = CRGB::Orange;
    leds[i+1] = CRGB::Orange;
    leds[NUM_LEDS_PER_STRIP - i + 1] = CRGB::Orange;
    leds[NUM_LEDS_PER_STRIP - i] = CRGB::Orange;
    
    FastLED.show();
    // clear our current dot before we move on
    //leds[i+3] = CRGB::Purple;
    delay(500);
  }
  // Pause for effect
  delay(500);
    
   // now turn them all green
   for(int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
    // set current dot to green
    leds[i] = CRGB::Green;
    FastLED.show();
  }
  
  delay(500);
}
