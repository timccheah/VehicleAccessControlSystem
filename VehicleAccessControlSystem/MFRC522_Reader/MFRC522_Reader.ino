#include <deprecated.h>
#include <stdbool.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>
#include <SPI.h>
#include <require_cpp11.h>
#include <EEPROM.h>         // EEPROM (memory) library

//#include <HC-SR04_Proximity_Sensor.ino>

/*
 * Pin Layout for Arduino Mega:
 * ------------------------------------
 * Signal      MFRC522 Reader/PCD Pin        Arduino Mega Pin                       
 * -------------------------------------------------
 * RST/Reset   RST                           5         
 * SPI SS      SDA(SS)                       53        
 * SPI MOSI    MOSI                          51        
 * SPI MISO    MISO                          50       
 * SPI SCK     SCK                           52        
*/


#define RST_PIN         5          // MFRC522 reference to pin on Arduino
#define SS_PIN          53         // MFRC522 reference to pin on Arduino

#define COMMON_ANODE
#ifdef COMMON_ANODE
#define LED_ON LOW
#define LED_OFF HIGH
#else
#define LED_ON HIGH
#define LED_OFF LOW
#endif

#define redLED 22    // LED reference to pin on Arduino
#define greenLED 23  // LED reference to pin on Arduino
#define yellowLED 24   // LED reference to pin on Arduino

boolean authorized = false;          // Initialize authorized card to false
boolean programMode = false;  // Initialize programming mode to false



/*
byte readCard[4];
int successRead;

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
MFRC522::MIFARE_Key key;           // Creates MIFARE key instances

void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}

void ShowReaderDetails() {
    // Get the MFRC522 software version
    byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
    Serial.print(F("MFRC522 Software Version: 0x"));
    Serial.print(v, HEX);
    if (v == 0x91)
        Serial.print(F(" = v1.0"));
    else if (v == 0x92)
        Serial.print(F(" = v2.0"));
    else
        Serial.print(F(" (unknown)"));
    Serial.println("");
    // When 0x00 or 0xFF is returned, communication probably failed
    if ((v == 0x00) || (v == 0xFF)) {
        Serial.println(F("WARNING: Communication failure?"));
    }
}
*/

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of class

MFRC522::MIFARE_Key key;

// Init array that store new NUID
byte nuidPICC[4];
int distance;

void setup() {
  
  
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  Exit_MFRC522_Setup();
  HC_SR04Setup();
  servoSetup();
}

 
void loop() {

  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

 for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
   
  printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
   rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();


  Exit_MFRC522_Loop();
  HR_SR04Loop();
 if (check(distance) == true) {
    servoLoop();
 }
}


void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }

}
