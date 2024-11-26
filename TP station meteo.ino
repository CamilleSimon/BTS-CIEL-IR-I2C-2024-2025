#include <LiquidCrystal_I2C.h>

// Création d'un objet LCD avec l'adresse I2C de l'écran
LiquidCrystal_I2C lcd(0x20, 16, 2);

const int PIN_TEMPERATURE = A0;
const int PIN_HUMIDITY = A1;
const int PIN_PRESSURE = A2;
const int PIN_LIGHT = A3;

float temperature;
float humidite;
float pression;
float confortThermique;


void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
}


void lectureTemperature()
{
  temperature = analogRead(Pin_TEMERATURE);
  Serial.print(temperature);
}


void lectureHumidite()
{
  humidite = analogRead(Pin_HUMIDITY);
  Serial.print(humidite);
}


void lecturePression()
{
  pression = analogRead(Pin_PRESSURE);
  Serial.print(pression);
}


void calculConfortThermique()
{
  confortThermique = 0.5 * (temperature + 61.0 + ((temperature - 68.0) * 1.2) + ((humidite) * 0.094 //RH pas fini !!
}


void loop()
{
  
}
