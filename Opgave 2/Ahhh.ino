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
  }else
    {
      for(int i = 0; i < 5; i++){
        if(storeTemp[i] = uidString){
            storeTemp[i] = "";
        }
    }
    digitalWrite(redLED, HIGH);
    delay(200);
    digitalWrite(redLED,LOW);
    Serial.println("Checked Out");
  }
  delay(10);

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}
 
void readRFID() {
  rfid.PICC_ReadCardSerial();
  Serial.print("Tag UID: ");
  uidString = String(rfid.uid.uidByte[0]) + " " + String(rfid.uid.uidByte[1]) + " " + 
    String(rfid.uid.uidByte[2]) + " " + String(rfid.uid.uidByte[3]);
  Serial.println(uidString);
  delay(200);
  
  if(storeTemp[0] != uidString && storeTemp[1] != uidString && storeTemp[2] != uidString && storeTemp[3] != uidString){
    digitalWrite(greenLED, HIGH);
    delay(200);
    digitalWrite(greenLED,LOW);
    Serial.println("Checked In");
    
    for(int i = 0; i = 4; i++){
        /*if(storeTemp[i] != NULL){
            storeTemp[i] = uidString;
            return;
        }*/
        storeTemp[i] = uidString;
    }
  }
}
 
/*void SignOut(){
    for(int i = 0; i < 5; i++){
        if(storeTemp[i] = uidString){
            storeTemp[i] = "";
        }
    }
    digitalWrite(redLED, HIGH);
    delay(200);
    digitalWrite(redLED,LOW);
    Serial.println("Checked Out");    
}*/