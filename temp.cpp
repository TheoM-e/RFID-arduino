int cards[] = {3, 2, 1, 3, 3};

void loop() {

    // change card with pb
    if (digitalRead(RFID_PB1) == LOW) {
        rfidPb2Value < ((sizeof(cards) / sizeof(int)) - 1) ? rfidPb2Value++ : (rfidPb2Value = 0);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Carte ");
        lcd.print(rfidPb2Value);
        lcd.print(" [");
        lcd.print(cards[rfidPb2Value]);
        lcd.print("].");
        Serial.print("A ");
        delay(1500);
        lcd.clear();
    }
    
    // do nothing until card scanned
    if (digitalRead(RFID_PB2) == HIGH) {
        lcd.setCursor(0, 0);
        lcd.print("Scannez votre carte");
        Serial.print("B ");
        return;
    }
    
    /* Code effectué après qu'une carte ait été scannée */
}
