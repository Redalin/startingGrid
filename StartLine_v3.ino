// MirroringSample - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers.  In this example, we're going to set up four NEOPIXEL strips on four
// different pins, and show the same thing on all four of them, a simple bouncing dot/cyclon type pattern

#include "FastLED.h"

#define NUM_LEDS 40
#define DATA_PIN 2
#define START_PIN 3
CRGB leds[NUM_LEDS];
int brightness = 82;
int car1Laptimes[6]
int car2Laptimes[6]
int car3Laptimes[6]

// For mirroring strips, all the "special" stuff happens just in setup.  We
// just addLeds multiple times, once for each strip
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // declare the ledPin as an OUTPUT
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void startSequence() {
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

void showLapCounters(car1, car2, car3) {
  #define LED_START
  #define LED_END
  
  // all lap displays should have the same number of LEDs, therefore we can divide the number by 3
  int numLedsPerCar = (LED_END - LED_START / 3)
  int car1Leds = 
}

void loop() {
  LEDS.setBrightness(brightness);
  // limit my draw to 1A at 5v of power draw
  FastLED.setMaxPowerInVoltsAndMilliamps(5,1000); 
  if (START_PIN) {
    // If somebody presses the start button - begin the countdown sequence
    startSequence();
  }

  // Read the values from the sensors to count laps for each car
  // start the lap timers for the 3 cars and display their number of laps
  showLapCounters(car1Laptimes.length, car2Laptimes.length, car3Laptimes.length);
  
}
