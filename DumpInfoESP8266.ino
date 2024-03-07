#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>

#define RST_PIN 0   // Reset pin connected to GPIO pin 0 (D3) on ESP8266
#define SS_PIN 15   // SPI SS (Slave Select) pin connected to GPIO pin 15 (D8) on ESP8266

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
    Serial.begin(9600);     // Initialize serial communications with the PC
    while (!Serial);        // Wait for the serial port to be opened
    SPI.begin();            // Init SPI bus
    mfrc522.PCD_Init();     // Init MFRC522
    delay(4);               // Optional delay. Some boards may need more time after init to be ready
    mfrc522.PCD_DumpVersionToSerial();   // Show details of PCD - MFRC522 Card Reader details
    Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if (!mfrc522.PICC_IsNewCardPresent()) {
        return;
    }

    // Select one of the cards
    if (!mfrc522.PICC_ReadCardSerial()) {
        return;
    }

    // Dump debug info about the card; PICC_HaltA() is automatically called
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
