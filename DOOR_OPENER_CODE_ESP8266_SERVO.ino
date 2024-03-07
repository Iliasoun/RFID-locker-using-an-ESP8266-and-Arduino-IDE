#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <Servo.h>

#define RST_PIN 0     // Reset pin connected to GPIO pin 0 (D3) on ESP8266
#define SS_PIN 15     // SPI SS (Slave Select) pin connected to GPIO pin 15 (D8) on ESP8266
#define SERVO_PIN 4  // Servo control pin connected to GPIO pin 14 (D2) on ESP8266

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
Servo myServo;                     // Create Servo instance

// Define the authorized UID
byte authorizedUID[] = {0x54, 0xD9, 0x82, 0x24};

bool cardPresent = false;

void setup() {
  Serial.begin(9600);          // Initialize serial communications with the PC
  while (!Serial);             // Wait for the serial port to be opened
  SPI.begin();                 // Init SPI bus
  mfrc522.PCD_Init();          // Init MFRC522
  myServo.attach(SERVO_PIN);   // Attach servo to pin D5
  resetServo();                // Reset servo to initial position
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {
      // Compare the UID of the detected card with the authorized UID
      if (compareUID(mfrc522.uid.uidByte, authorizedUID, mfrc522.uid.size)) {
        Serial.println("Authorized card detected! Opening the door ...");
        turnServo();
        delay(5000); // Wait for 5 seconds
        Serial.println("Closing the door ...");
        resetServo();
      } else {
        Serial.println("Unauthorized card detected!");
      }
      
      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();
    }
  }
}

void turnServo() {
  myServo.write(180); // Rotate servo to 180 degrees
}

void resetServo() {
  myServo.write(0); // Return servo to initial position
}

// Function to compare two RFID UIDs
bool compareUID(byte *uid1, byte *uid2, byte size) {
  for (byte i = 0; i < size; i++) {
    if (uid1[i] != uid2[i]) {
      return false;
    }
  }
  return true;
}
