/* Connection pins:
Arduino     Soil Moisture Sensor YL-69
  A0             Analog A0
  5V               VCC
  GND              GND
*/
#include <Servo.h> 
#include <Adafruit_NeoPixel.h>
#define PIN 5
Servo myservo;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT); //set up analog pin 0 to be input
  myservo.attach(9);

}

void loop()
{
  int moist = analogRead(A0); //take a sample
  Serial.print(moist); Serial.print(" - ");
  
  if(moist >= 1000) {
   Serial.println("Sensor is not in the Soil or DISCONNECTED");
   for(int i=0;i<12;i++){
  strip.begin();
  strip.setPixelColor(i,255,0,0);
  strip.show();
    }

  }
  if(moist < 1000 && moist >= 750) { 
   Serial.println("Soil is DRY");
      for(int i=0;i<12;i++){
  strip.begin();
  strip.setPixelColor(i,153,76,0);
  strip.show();
    }
 
  }
  if(moist < 750 && moist >= 500) {
   Serial.println("Soil is HUMID");
      for(int i=0;i<12;i++){
  strip.begin();
  strip.setPixelColor(i,153,153,0);
  strip.show();
    } 

  }
  if(moist < 500 && moist >= 300) {
   Serial.println("Soil is very HUMID"); 
   for(int i=0;i<12;i++){
  strip.begin();
  strip.setPixelColor(i,255,255,0);
  strip.show();
    }
  }
  if(moist < 300) {
   Serial.println("Sensor in WATER");
   myservo.write(180);
      for(int i=0;i<12;i++){
  strip.begin();
  strip.setPixelColor(i,0,153,0);
  strip.show();
    }

 
  }
  delay(2000);
}
