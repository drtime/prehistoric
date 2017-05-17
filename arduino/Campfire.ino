#include <Adafruit_NeoPixel.h>
#define PIN 5

Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

int counter = 0;

void setup() {
  //strip settings
  strip.setBrightness(5);

  Serial.begin(9600);
}

void loop() {

  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  // print the results to the serial monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.print(outputValue);
  Serial.print("\t count = ");
  Serial.println(counter);

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);

  if(sensorValue > 500 && sensorValue <550){
      counter++;
    }

  if(counter > 5){
 
  for(int i=0;i<12;i++){
  strip.begin();
  strip.setPixelColor(i,255,0,0);
  strip.show();
    }
  delay(50);
  for(int i=0;i<12;i++){
    strip.begin();
    strip.setPixelColor(i,0,0,0);
    strip.show();
    }
    delay(50);
    
  }
 }

