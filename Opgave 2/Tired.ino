#include <MFRC522.h> // for the RFID
#include <SPI.h> // for the RFID
 
// define pins for RFID
#define CS_RFID 10
#define RST_RFID 9
 
// Instance of the class for RFID
MFRC522 rfid(CS_RFID, RST_RFID); 
 
// Variable to hold the tag's UID
String uidString;
String storeTemp[4];
 
// Define check in time
//const int checkInHour = 9;
//const int checkInMinute = 5;
 
//Variable to hold user check in
//int userCheckInHour;
//int userCheckInMinute;
 
// Pins for LEDs and buzzer
const int redLED = 6;
const int greenLED = 4;
 
void setup() {
  
  // Set LEDs and buzzer as outputs
  pinMode(redLED, OUTPUT);  
  pinMode(greenLED, OUTPUT);
  
  // Init Serial port
  Serial.begin(9600);
  
  // Init SPI bus
  SPI.begin(); 
  // Init MFRC522 
  rfid.PCD_Init(); 
}
 
void loop() {
  //look for new cards
  if(rfid.PICC_IsNewCardPresent()) {
    readRFID();
  }

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}
 
void readRFID() {
  rfid.PICC_ReadCardSerial();
  Serial.print("Tag UID: ");
  uidString = String(rfid.uid.uidByte[0]) + String(rfid.uid.uidByte[1]) + 
    String(rfid.uid.uidByte[2]) + String(rfid.uid.uidByte[3]);
  Serial.println(uidString);
  delay(200);

  for(int j = 0; j = storeTemp->length(); j++){
      if(storeTemp[j] != NULL){
            digitalWrite(greenLED, HIGH);
            delay(200);
            digitalWrite(greenLED,LOW);
            Serial.println("Checked In");
            logCard();
      }
  }
  
  /*for(int i = 0; i == storeTemp->length(); i++){
    if(storeTemp[0] != uidString){
        digitalWrite(greenLED, HIGH);
        delay(200);
        digitalWrite(greenLED,LOW);
        Serial.println("Checked In");
        logCard();
    }
    else {
        digitalWrite(redLED, HIGH);
        delay(200);
        digitalWrite(redLED,LOW);
        Serial.println("Checked Out");    
        SignOut();
    }
  }*/
}
 
void logCard() {
    for(int i = 0; i == storeTemp->length(); i++){
        if(storeTemp[i] != NULL){
            storeTemp[i] = uidString;
        }
    }
}

void SignOut(){
    digitalWrite(redLED, HIGH);
    delay(200);
    digitalWrite(redLED,LOW);
    Serial.println("Checked Out"); 

    for(int i = 0; i == storeTemp->length(); i++){
        if(uidString == storeTemp[i]){
            storeTemp[i] = "";
        }
    }
}