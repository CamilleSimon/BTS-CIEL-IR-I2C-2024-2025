// C++ code
//

#include <Wire.h>
#include <LiquidCrystal_I2C.h>



// Création d'un objet LCD avec l'adresse I2C de l'écran
LiquidCrystal_I2C lcd(0x27, 16, 2);
int humidite = 0;
int temp = 0;

void setup()
{
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  
  // initialisation capteur
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  
  
  Serial.begin(9600);
}

void loop()
{
  humidite = analogRead(A3);
  temp = round(analogRead(A2)*(5.0/1024.0)*100-50);
  Serial.println(temp);
  lcd.setCursor(0,0);
  lcd.print("humidite : ");
  lcd.print(humidite);
  lcd.print("      ");
  lcd.setCursor(0,1);
  lcd.print("temps c : ");
  lcd.print(temp);
  lcd.print(" C   ");
  delay(200); 
}
