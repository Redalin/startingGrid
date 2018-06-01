//#include <FastIO.h>
//#include <I2CIO.h>
//#include <LCD.h>
//#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
//#include <LiquidCrystal_I2C_ByVac.h>
//#include <LiquidCrystal_SI2C.h>
//#include <LiquidCrystal_SR.h>
//#include <LiquidCrystal_SR1W.h>
//#include <LiquidCrystal_SR2W.h>
//#include <LiquidCrystal_SR3W.h>
//#include <SI2CIO.h>
//#include <SoftI2CMaster.h>

// Adafruit NeoPixel - Version: Latest 
#include <Adafruit_NeoPixel.h>

// MirroringSample - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers.  In this example, we're going to set up four NEOPIXEL strips on four
// different pins, and show the same thing on all four of them, a simple bouncing dot/cyclon type pattern
// tamiya lap timer project:
// http://www.instructables.com/id/Lap-Timer-Mini-4WD-IR-Sensor-/


#include "FastLED.h"


#define NUM_LEDS 20
#define DATA_PIN 13
#define START_PIN 6
CRGB leds[NUM_LEDS];
int brightness = 255;
int car1Laptimes[6];
int car2Laptimes[6];
int car3Laptimes[6];
int car1Laps = 0;
int car2Laps = 0;
int car3Laps = 0;

// set the LCD address to 0x27 for a 16 chars 2 line display
// A FEW use address 0x3F
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address


// For mirroring strips, all the "special" stuff happens just in setup.  We
// just addLeds multiple times, once for each strip
void setup() {
  // limit power draw to 1A at 5v of power draw
  FastLED.setMaxPowerInVoltsAndMilliamps(5,1000); 
  pinMode(DATA_PIN, OUTPUT);  // declare the DATA_PIN as an OUTPUT
  pinMode(START_PIN, INPUT);  // declare the StartPin as an INPUT - this is for the pushbutton
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  // ------- Quick 3 blinks of backlight  -------------
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); // finish with backlight on  
}

void startSequence() {
  lcd.clear();
  lcd.setCursor(4,0); 
  lcd.print("READY!");
  for(int i = 0; i < NUM_LEDS; i++) {
    // set all leds to Orange
    leds[i] = CRGB::Orange;
  }
  FastLED.show();
  delay(10000);

  // Wait 10 sec and turn them off in stages
  int blockSize = 4;
  lcd.setCursor(5,1); 
  lcd.print("SET!");
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
  lcd.clear();
  lcd.setCursor(2,0); 
  lcd.print("GO! GO! GO!"); 
  lcd.setCursor(3,1); 
  lcd.print("GO! GO! GO!");
   // now GO!! Turn them all green
   for(int i = 0; i < NUM_LEDS; i++) {
    // set current dot to green
    leds[i] = CRGB::Green;
    FastLED.show();
  }
  // Done.
}

void clearBoard() {
  for(int i = 0; i < NUM_LEDS; i++) {
    // set all leds to Off/black
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(500);
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

void displayLCDintro() {
  lcd.clear();
  lcd.setCursor(3,0); 
  lcd.print("Racewars!         Racewars!");
  lcd.setCursor(0,1);
  lcd.print("Press Button to begin countdown");
  // scroll to the left to move it offscreen right:
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    if (digitalRead(START_PIN)) {
      // If somebody presses the start button - begin the countdown sequence
      startSequence();
    }
    delay(300);
  }

  // scroll to the right to move it offscreen right:
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    // scroll one position right:
    lcd.scrollDisplayRight();
    if (digitalRead(START_PIN)) {
      // If somebody presses the start button - begin the countdown sequence
      startSequence();
    }
    delay(300);
  }

  // delay at the end of the full loop:
  delay(1000);
}

void loop() {
  displayLCDintro();

  if (digitalRead(START_PIN)) {
    // If somebody presses the start button - begin the countdown sequence
    startSequence();
  } else {
    clearBoard();
  }
  
  // Read the values from the sensors to count laps for each car
  // start the lap timers for the 3 cars and display their number of laps
  
  // showLapCounters(car1Laptimes.length, car2Laptimes.length, car3Laptimes.length);
  
}

