#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include <Arduino.h>

# define CNY        A0
# define PUMP       2 // led / motor
# define WATER_LVL  3 // pb
# define RFID_PB1   4 // pb
# define RFID_PB2   5 // pb

int cards[] = {3, 2, 1, 3, 3};
int inputPins[] = {RFID_PB1, RFID_PB2, WATER_LVL};
int outputPins[] = {PUMP};
int rfidPb2Value = 0;

// init lcd screen
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setupPin(int inputPins[], int outputPins[]);

void setup() {
    // input & output pin initialization
    //setupPin(inputPins, outputPins);

    pinMode(RFID_PB1, INPUT_PULLUP);
    pinMode(RFID_PB2, INPUT_PULLUP);
    pinMode(WATER_LVL, INPUT_PULLUP);
    pinMode(PUMP, OUTPUT);

    Serial.begin(9600);

    // lcd initialization
    lcd.init();
}


void loop() {

    // change card with pb
    if (digitalRead(RFID_PB1) == LOW){
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

    // no more drink
    if (cards[rfidPb2Value] == 0) {
        lcd.setCursor(0, 0);
        lcd.print("Credits insuffisants");
        Serial.print("C ");

        delay(1500);
        lcd.clear();
        return;
    }

    // not enought water
    if (digitalRead(WATER_LVL) == LOW) {
        lcd.setCursor(0, 0);
        lcd.print("Niveau d'eau insuffisant");
        Serial.print("D ");

        delay(1500);
        lcd.clear();
        return;
    }

    // glass present ?
    if (analogRead(CNY) < 100) {
        lcd.setCursor(0, 0);
        lcd.print("Verre absent");
        Serial.print("E ");

        delay(1500);
        lcd.clear();
    } else {
        lcd.setCursor(0, 0);
        lcd.print("Distribution...");
        cards[rfidPb2Value] -= 1;
        digitalWrite(PUMP, HIGH);
        delay(3000);
        digitalWrite(PUMP, LOW);
        lcd.clear();
    }

}

void setupPin(int inputPins[], int outputPins[]) {
    for (int i; i < sizeof(inputPins) / sizeof(int); i++) {
        pinMode(i, INPUT_PULLUP);
    }

    for (int i; i < sizeof(outputPins) / sizeof(int); i++) {
        pinMode(i, OUTPUT);
    }
}
