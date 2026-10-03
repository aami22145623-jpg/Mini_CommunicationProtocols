#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);

const int POT_PIN = A0;

void setup()
{
    Serial.begin(9600);

    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("Smart Monitor");

    delay(1000);

    lcd.clear();
}

void loop()
{
    // Read potentiometer
    int adcValue = analogRead(POT_PIN);

    // Convert 0-1023 to 0-100
    int value = map(adcValue, 0, 1023, 0, 100);

    // Send value to ATmega32
    Serial.println(value);

    // Display value
    lcd.setCursor(0, 0);
    lcd.print("Value: ");
    lcd.print(value);
    lcd.print("   ");

    // Display status
    lcd.setCursor(0, 1);

    if (value < 40)
    {
        lcd.print("Status: NORMAL ");
    }
    else if (value < 70)
    {
        lcd.print("Status: MEDIUM ");
    }
    else
    {
        lcd.print("Status: HIGH   ");
    }

    delay(500);
}