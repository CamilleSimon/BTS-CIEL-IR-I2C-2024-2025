```C++

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Création d'un objet LCD avec l'adresse I2C de l'écran
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
}
void loop()
{
  lcd.setCursor(0,0);
  lcd.print("1er nombre:");
  lcd.setCursor(0,1);
  if(Serial.available() > 0)
  {
    char nombre = Serial.read();
    lcd.print(nombre);
  }
}

```
