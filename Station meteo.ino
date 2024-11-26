// C++ code
//
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2);

const float PIN_TEMPERATURE = A0;
const float PIN_HUMIDITY = A1;
const float PIN_PRESSURE = A2;
const float PIN_LIGHT = A3;
const float temp;
const float hum;
const float pres;
const float light;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  
  displayStartUpMessage();
}

void setCapteur()
{
  temp = analogRead(PIN_TEMPERATURE);
}

void getCapteur()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature : ");
  lcd.print(temp);
  delay(2000);
  lcd.clear();
  lcd.print("Humidite : ");
  lcd.print(hum);
  delay(2000);
  lcd.clear();
  lcd.print("Pression : ");
  lcd.print(pres);
  delay(2000);
  lcd.clear();
  lcd.print("Luminosite : ");
  lcd.print(light);
  delay(2000);
}

void displayStartUpMessage()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Station Meteo");
  lcd.setCursor(0, 1);
  lcd.print("Initialisation...");
  delay(2000);
  lcd.clear();
}

void loop()
{
  getCapteur();
}
