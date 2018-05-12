// Date and time functions using a DS3231 RTC connected via I2C and Wire Lib
// Clock code to make a LED strip perform functions based on time.

// Setup for the RTC
#include <Wire.h>
#include "RTClib.h"  // Credit: Adafruit
RTC_DS1307 RTC;

// Setup for LED
const int ledPin =  3;      // the number of the LED pin
#include "FastLED.h"

#define TOTAL_LEDS_PER_STRIP 12
CRGB leds[TOTAL_LEDS_PER_STRIP];

void setup() {
 
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // tell FastLED there's  NEOPIXEL leds on pin 3
  FastLED.addLeds<NEOPIXEL, ledPin>(leds, TOTAL_LEDS_PER_STRIP);
  
  // Begin the Serial connection 
  Serial.begin(9600);
 
  // Instantiate the RTC
  Wire.begin();
  RTC.begin();
 
  // Check if the RTC is running.
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running");
  }

  // This section grabs the current datetime and compares it to
  // the compilation time.  If necessary, the RTC is updated.
  DateTime now = RTC.now();
  DateTime compiled = DateTime(__DATE__, __TIME__);
  if (now.unixtime() < compiled.unixtime()) {
    Serial.println("RTC is older than compile time! Updating");
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
 
  Serial.println("Setup complete.");
}


void loop() {
  // Get the current time
  DateTime now = RTC.now();   
  
  // set the LEDs to low brightness
  FastLED.setBrightness(24);
  
  int currentSecond = now.minute();
  int secondLED = currentSecond/5;
  
  // Move a light up every 5 seconds
  // make all LEDs up to secondLED Orange, but have the 3, 6 and 9 points slightly different.
  for(int i = 0; i < secondLED; i++) {
    leds[i] = CRGB::Red;
    if(i == 2) { leds[i] = CRGB::Orange; }
    if(i == 5) { leds[i] = CRGB::Yellow; }
    if(i == 8) { leds[i] = CRGB::Orange; }
  }
  // Make all remaining LEDs black (off)
  for(int i = secondLED; i < TOTAL_LEDS_PER_STRIP; i++) {
    leds[i] = CRGB::Black;
  }
  leds[TOTAL_LEDS_PER_STRIP] = CRGB::White;
  leds[TOTAL_LEDS_PER_STRIP-1] = CRGB::White;
  //display them all
  FastLED.show();
 
  // Display the current time
//  Serial.print("Current second: ");
//  Serial.print(now.year(), DEC);
//  Serial.print('/');
//  Serial.print(now.month(), DEC);
//  Serial.print('/');
//  Serial.print(now.day(), DEC);
//  Serial.print(' ');
//  Serial.print(now.hour(), DEC);
//  Serial.print(':');
//  Serial.print(now.minute(), DEC);
//  Serial.print(':');
//  Serial.print(now.second(), DEC);
//  Serial.print(currentSecond, DEC);
//  Serial.print(secondLED, DEC);
//  Serial.println();
 
  delay(10000);
}
