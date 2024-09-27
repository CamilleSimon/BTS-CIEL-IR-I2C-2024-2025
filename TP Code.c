#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
String firstnumb = "";
String secondnumb = "";
bool choix1 = false;
bool choix2 = false;
bool affichageNombre = false; 
char operation;

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
    firstnumb = Serial.readStringUntil('\n');
    firstnumb.trim();
    if (firstnumb.length() > 0) {
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
    secondnumb = Serial.readStringUntil('\n'); 
    secondnumb.trim(); 
    if (secondnumb.length() > 0) {
      choix2 = true;
      affichageNombre = false;
    }
  }
  if (choix1 && choix2 && !affichageNombre) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Choisi le symbole:");
    affichageNombre = true;
  }
  if (choix1 && choix2 && Serial.available() > 0) {
    operation = Serial.read();
    if (operation == '+' || operation == '-' || operation == '*' || operation == '/') {
      float num1 = firstnumb.toFloat();
      float num2 = secondnumb.toFloat();
      float result = 0.0;
      switch (operation) {
        case '+':
          result = num1 + num2;
          break;
        case '-':
          result = num1 - num2;
          break;
        case '*':
          result = num1 * num2;
          break;
        case '/':
          if (num2 != 0) { 
            result = num1 / num2;
          } else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Erreur: Div 0");
            return;
          }
          break;
      }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Resultat: ");
      lcd.print(String(result, 4));
    }
  }
}
