#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  
}

void loop() {
  int humidite = analogRead(A0);
  

   
   // Mesure la tension sur la broche A1
  float valBrute = analogRead(A1);
  // Calcul de la température en degré Celcius
  float valTemp = valBrute * (5.0/1023.0 *100.0);


  // Affichage sur LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Temperature : ");
  lcd.setCursor(1,1);
  lcd.print(valTemp);
  lcd.setCursor(1,2);
  lcd.print(" Celcius");
  delay(1000);
  
  
  
  delay(200);
}
