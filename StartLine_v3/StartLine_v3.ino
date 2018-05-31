// Adafruit NeoPixel - Version: Latest 
#include <Adafruit_NeoPixel.h>

// MirroringSample - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers.  In this example, we're going to set up four NEOPIXEL strips on four
// different pins, and show the same thing on all four of them, a simple bouncing dot/cyclon type pattern
// tamiya lap timer project:
// http://www.instructables.com/id/Lap-Timer-Mini-4WD-IR-Sensor-/


#include "FastLED.h"

#define NUM_LEDS 20
#define DATA_PIN 2
#define START_PIN 3
CRGB leds[NUM_LEDS];
int brightness = 255;
int car1Laptimes[6];
int car2Laptimes[6];
int car3Laptimes[6];
int car1Laps = 0;
int car2Laps = 0;
int car3Laps = 0;

// For mirroring strips, all the "special" stuff happens just in setup.  We
// just addLeds multiple times, once for each strip
void setup() {
  // limit power draw to 1A at 5v of power draw
  FastLED.setMaxPowerInVoltsAndMilliamps(5,1000); 
  pinMode(DATA_PIN, OUTPUT);  // declare the DATA_PIN as an OUTPUT
  pinMode(START_PIN, INPUT);  // declare the StartPin as an INPUT - this is for the pushbutton
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void startSequence() {
  for(int i = 0; i < NUM_LEDS; i++) {
    // set all leds to Orange
    leds[i] = CRGB::Orange;
  }
  FastLED.show();
  delay(10000);

  // Wait 10 sec and turn them off in stages
  int blockSize = 4;
  for(int i = 0; i < NUM_LEDS; i++) {
    // Turn every LED red
    leds[i] = CRGB::Red;
    
    // Only show them if we're going to show a whole light block
    int x = (i + 1) % blockSize;
    if (x == 0) {
      FastLED.show();
      delay(1000);
    }
  }
  
  // pause for effect - a random time between 1.5 and 2.5 seconds
  delay(random(1500, 2500));
    
   // now GO!! Turn them all green
   for(int i = 0; i < NUM_LEDS; i++) {
    // set current dot to green
    leds[i] = CRGB::Green;
    FastLED.show();
  }
  // Done.
}


/*void showLapCounters() {
  #define LED_START
  #define LED_END
  
  // all lap displays should have the same number of LEDs, therefore we can divide the number by 3
  int numLedsPerCar = (LED_END - LED_START/3)
  int car1Leds = 0;
  
  return;
}
*/

void loop() {
  if (digitalRead(START_PIN)) {
    // If somebody presses the start button - begin the countdown sequence
    startSequence();
  }

  // Read the values from the sensors to count laps for each car
  // start the lap timers for the 3 cars and display their number of laps
  
  // showLapCounters(car1Laptimes.length, car2Laptimes.length, car3Laptimes.length);
  
}

