#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include <Arduino.h>

# define CNY        A0
# define WATER_LVL   2
# define PUMP       3
# define WATER      4
# define RFID_PB1   5
# define RFID_PB2   6

int cards[] = {3, 2, 1, 3, 3};
int inputPins[] = {CNY, RFID_PB1, RFID_PB2, WATER, WATER_LVL};
int outputPins[] = {PUMP};
int rfidPb2Value = 0;

// init lcd screen
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setupPin(int inputPins[], int outputPins[]);

void setup() {
    // input & output pin initialization
    setupPin(inputPins, outputPins);

    // lcd initialization
    lcd.init();
    lcd.setCursor(0, 0);
    lcd.print("innitializing");
    delay(3000);
    lcd.clear();
}


void loop() {

    // change card with pb
    if (digitalRead(RFID_PB1) == LOW)
        rfidPb2Value < ((sizeof(cards) / sizeof(int)) - 1) ? rfidPb2Value++ : (rfidPb2Value = 0);

    // do nothing until card scanned
    if (digitalRead(RFID_PB2) == HIGH) {
        return;
    }

    // no more drink
    if (cards[rfidPb2Value] == 0) {
        lcd.setCursor(0, 0);
        lcd.print("Credits insuffisants");
        delay(1500);
        lcd.clear();
        return;
    }

    // not enought water
    if (digitalRead(WATER_LVL) == LOW) {
        lcd.setCursor(0, 0);
        lcd.print("Niveau d'eau insuffisant");
        delay(1500);
        lcd.clear();
        return;
    }

    // glass present ?
    if (analogRead(CNY) < 100) {
        lcd.setCursor(0, 0);
        lcd.print("Verre absent");
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
        pinMode(i, INPUT);
    }

    for (int i; i < sizeof(outputPins) / sizeof(int); i++) {
        pinMode(i, OUTPUT);
    }
}
