RFID Door Opener using Wemos D1 Mini

Overview:
This project utilizes a Wemos D1 Mini microcontroller along with an RFID module to create a door opener system. When a compatible RFID card is scanned, the system activates a servo motor to unlock the door temporarily.

Setup:
1. Wiring:
   - Connect the RFID module to the Wemos D1 Mini as per the provided "Wemos RFID Wiring Diagram".
   - Note that pin 4 on the Wemos D1 Mini corresponds to the D2 pin.

Usage:
1. Scan RFID Cards:
   - Upload the "DumpInfoESP8266.ino" code to the Wemos D1 Mini.
   - Open the serial monitor to view the UID codes of scanned RFID cards.
   - Note down the UID code of the card you want to grant access. The UID code should be in the format: "0x54, 0xD9, 0x82, 0x24" instead of "54 D9 82 24" given on the serial monitor during the scan (this code is an example).

2. Software:
   - Use the "DOOR_OPENER_CODE_ESP8266_SERVO.ino" code for the main functionality.
   - Before uploading the code, ensure to modify the UID code on line 14 to match the one obtained from the serial monitor during RFID card scanning.
   - The UID code should be in the format: "0x54, 0xD9, 0x82, 0x24" (this code is an example).

3. Upload and Activate:
   - Upload the modified main code to the Wemos D1 Mini microcontroller.
   - Once the system is powered on, it will read RFID cards. If a matching card is detected, the servo motor will rotate 180° temporarily unlocking the door.

Note:
- Ensure proper connections and power supply to avoid any damage to the components.
- This project serves as a basic implementation and can be expanded for more advanced features such as multiple user support, logging, etc.
