#include "SPI.h"
#include "MFRC522.h"

#define SS_PIN 10
#define RST_PIN 9
#define SP_PIN 8
 String readCards[3] = {"B5:8B:D1:65","91:F4:5A:8D","51:35:A6:6C"};
 String newArray[3];
MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

int counter = 0;

String n01 = "B5:8B:D1:65";
String n02 = "51:35:A6:6C";
String n03 = "91:F4:5A:8D"; 

String mission[3];
String succes[3] = {n01, n02, n03};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  while(counter < 3){
    
     if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();
  
    if(strID == n01 || strID == n02 || strID == n03){
      counter++;
      if(counter == 1){
        mission[0] = strID;
        Serial.println("first scan: " + mission[0] + " count: " + counter);
        strID = "";
        delay(1000);
        Serial.println("next scan please");
      } else if(counter == 2){
        mission[1] = strID;
        Serial.println("second scan: " + mission[1] + " count: " + counter);
        strID = "";
        delay(1000);
        Serial.println("next scan please");
      } else if(counter == 3){
        mission[2] = strID;
        Serial.println("third scan: " + mission[2] + " count: " + counter);
        strID = "";
        delay(1000);
      }
     }
  }

for (int i=0;i<3;i++){
  Serial.println(mission[i]);
}
delay(5000);
    
     
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
