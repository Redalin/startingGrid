/*
LAP TIMER
Publish V 2 Beta 
09 February 2016
Implant to Arduino nano, 4pcs TCRT5000, LM358P,
By : Iqbal
Tested : Erik MR
Sensor : TCRT5000
*/

int sensorPin = 7; //
int sensorReading;
int previousSensorReading;
int ledPin =13; //LED monitor READ
int ledPin_2=12; // LED Waiting
int lap=0;
int currentLap=0;
int previousLap=0;

float dist = 10000; //put sensor no 4 and no 1= 1 meter distance
float speedkph;
unsigned long start, finished, elapsed;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup(){
  pinMode (sensorPin, INPUT_PULLUP);
  pinMode (ledPin_2, OUTPUT);
  Serial.begin (57600);
  Serial.print ("LAP TIMER B-V2");
}

void(*resetFunc)(void)=0; // For Reset Counter


void displayResult(){
  float h, m, s, ms,cr;
  unsigned long over;
  elapsed = finished - start ;
  h = int (elapsed/360000);
  over = elapsed%3600000;
  m= int(over/60000);
  over=over%60000;
  s=int(over/1000);
  ms=over%1000;
  cr=lap;

 Serial.print (m,0);
 Serial.print (" :");
 Serial.print ("  ");
 Serial.print (s,0);
 Serial.print (" :");
 Serial.print ("  ");
 Serial.print (ms,0);
 //Serial.print(" ms ");
 Serial.print("  ");  
 Serial.print("Lap : ");
 Serial.print(cr,0); 
 Serial.flush();

}

void speedometer(){
 
 elapsed = finished - start ;
 speedkph= dist/elapsed;
 Serial.print("           ");
 Serial.print("|");  
 Serial.print ("km/h : ");
 Serial.println (speedkph,0);
}


void loop(){

  sensorReading = digitalRead (sensorPin);
  if (sensorReading != previousSensorReading) {
    //reset the debounce timer
    lastDebounceTime = millis();
  }
  
  digitalWrite (ledPin_2,LOW);


  
  if (digitalRead(sensorPin)==true){ 
    start=millis();
    digitalWrite (ledPin,HIGH);
    currentLap =1;
  }
  
   else if (digitalRead(sensorPin)==false){
    finished = millis();
    digitalWrite (ledPin, LOW);
    currentLap=0;
    displayResult(); 
    speedometer();
  }
  
  if (currentLap!=previousLap){
    if(currentLap==1){
     lap=lap+1;     
   }

}

previousLap=currentLap;
delay(10);
//---------------Below is received command from pc---------------------
char data = Serial.read();  
switch (data){
case '0' : resetFunc();
case '1' : Serial.println("========End========"); digitalWrite (ledPin_2,HIGH);delay(12000); break;
case '2' : Serial.println ("||"),(elapsed);
}
}
