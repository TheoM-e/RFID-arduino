#include <SPI.h>
#include <MFRC522.h>
#include <SD.h>

#define RST_PIN         9
#define SS_PIN          10

MFRC522 rfid(SS_PIN, RST_PIN);
File sdFile;

void setup() {
	Serial.begin(9600);
	while (!Serial);		// Do nothing if no serial port is opened

  	// SD
	if (!SD.begin(4)) {
		Serial.println("SD card init. failed");
		while (1);
	}
	Serial.println("(+) SD");

	rfid.PCD_Init();		// Init MFRC522
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
  	sdFile = SD.open("datas.txt", FILE_WRITE);
  
  	// if file opened correctly
  	if (sdFile) {
		writeHex(rfid.uid.uidByte, rfid.uid.size, sdFile);
		file.close();
 	}  
	Serial.println("");

	rfid.PICC_HaltA();

}

void writeHex(byte *buffer, byte bufferSize, File file) {
  for (byte i = 0; i < bufferSize; i++) {
    file.print(buffer[i] < 0x10 ? " 0" : " ");
    file.print(buffer[i], HEX);
    file.println("");
  }
}
