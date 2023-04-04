#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9
#define SS_PIN          10

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
	Serial.begin(9600);
	while (!Serial);		// Do nothing if no serial port is opened
	mfrc522.PCD_Init();		// Init MFRC522
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! rfid.PICC_IsNewCardPresent()) {
		return ;
	}

	// Select one of the cards
	if ( ! rfid.PICC_ReadCardSerial()) {
		return ;
	}

	MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

  Serial.print(F("RFID Tag UID: "));
  printHex(rfid.uid.uidByte, rfid.uid.size);
  Serial.println("");

  rfid.PICC_HaltA();

}

void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
