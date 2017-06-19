
/* Connection pins:
Arduino     Soil Moisture Sensor YL-69
  A0             Analog A0
  5V               VCC
  GND              GND
*/

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT); //set up analog pin 0 to be input
  pinMode(2, OUTPUT); // green led
  pinMode(3, OUTPUT); // yellow led
  pinMode(4, OUTPUT); // yellow2 led
  pinMode(5, OUTPUT); // red led
}

void loop()
{
  int moist = analogRead(A0); //take a sample
  Serial.print(moist); Serial.print(" - ");
  
  if(moist >= 1000) {
   Serial.println("Sensor is not in the Soil or DISCONNECTED");
   digitalWrite(2, LOW);
   digitalWrite(3, LOW);
   digitalWrite(4, LOW);
   digitalWrite(5, HIGH);//red led gives assumpstion something is wrong 
  }
  if(moist < 1000 && moist >= 750) { 
   Serial.println("Soil is DRY");
   digitalWrite(2, LOW);
   digitalWrite(3, LOW);
   digitalWrite(4, LOW);
   digitalWrite(5, HIGH); 
  }
  if(moist < 750 && moist >= 500) {
   Serial.println("Soil is HUMID"); 
   digitalWrite(2, LOW);
   digitalWrite(3, LOW);
   digitalWrite(4, HIGH);//yellow lights start to turn on to in indicate something good is happening
   digitalWrite(5, LOW);
  }
  if(moist < 500 && moist >= 300) {
   Serial.println("Soil is very HUMID"); 
   digitalWrite(2, LOW);
   digitalWrite(3, HIGH);
   digitalWrite(4, LOW);
   digitalWrite(5, LOW);
  }
  if(moist < 300) {
   Serial.println("Sensor in WATER");
   digitalWrite(2, HIGH);//the soil is wet, puzzle is completed
   digitalWrite(3, LOW);
   digitalWrite(4, LOW);
   digitalWrite(5, LOW);
  }
  delay(60);
}

