```C++
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Création d'un objet LCD avec l'adresse I2C de l'écran
LiquidCrystal_I2C lcd(0x27, 16, 2);

float lectureTemperature()
{
  float tempvalue = analogRead(0);
  return ((tempvalue*5/1024)*100-50)*9/5+32;
}

float lectureHumidite()
{
  float humidityvalue = analogRead(1);
  return ((humidityvalue - 8)*100)/(875-8);
}

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
}
void loop()
{
  float tempvalue = lectureTemperature();
  lcd.print(tempvalue, 0);
  lcd.print("degres");
  lcd.setCursor(0,1);
  float humidityvalue = lectureHumidite();
  lcd.print(humidityvalue, 0);
  lcd.print("%");
  lcd.setCursor(0,0);
  delay(1000);
  lcd.clear();
  
}

```
