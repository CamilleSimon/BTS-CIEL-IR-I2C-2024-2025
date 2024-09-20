#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
float firstnumb;
float secondnumb;
bool choix1 = false;
bool choix2 = false;
bool affichageNombre = false; 
String operation;

void setup() {
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  choix();
}

void choix() {
  if (!choix1 && !affichageNombre) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Choisi 1er nombre:");
    affichageNombre = true;
  }
   if (!choix1 && Serial.available() > 0) {
    firstnumb = Serial.parseFloat();
    if (Serial.available() > 0 || firstnumb == 0) {
      choix1 = true;
      affichageNombre = false;
    }
  }
  if (choix1 && !choix2 && !affichageNombre) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Choisi 2eme nombre:");
    affichageNombre = true;
  }
  if (choix1 && !choix2 && Serial.available() > 0) {
    secondnumb = Serial.parseFloat();
    if (Serial.available() > 0 || secondnumb == 0) {
      choix2 = true;
      affichageNombre = false;
    }
  }
}
