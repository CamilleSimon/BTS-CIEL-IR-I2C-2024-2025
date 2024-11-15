```C
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Création d'un objet LCD avec l'adresse I2C de l'écran
LiquidCrystal_I2C lcd(0x27, 16, 2);

String nombre1;
String nombre2;
char symbole;
char valide[12] = {'0','1','2','3','4','5','6','7','8','9','.',','};
String receptionChiffre()
{
  String message = Serial.readStringUntil('\n');
  for(int i = 0 ; i<message.length(); i++)
  {
    for(int y = 0 ; y < 12 ; y++)
    {
      if(message[i] == valide[y])
      {
        Serial.println("OK");
      }
    }
  }
  return message;
}
char receptionOperation()
{
  char operation = Serial.read();
  return operation;
}
void calculatrice()
{
  if(nombre1 == NULL && nombre2 == NULL)
  {
    lcd.setCursor(0,0);
    lcd.print("1er nombre:");
    lcd.setCursor(0,1);
    while(Serial.available() > 0)
    {
      nombre1 = receptionChiffre();
      lcd.clear();
    }
  }
  else if(nombre1 != NULL && nombre2 == NULL)
  {
    lcd.setCursor(0,0);
    lcd.print("2eme nombre:");
    lcd.setCursor(0,1);
    while(Serial.available() > 0)
    {
      nombre2 = receptionChiffre();
      lcd.clear();  
    }
  }
  else if(nombre1 != NULL && nombre2 != NULL && symbole == NULL)
  {
    lcd.setCursor(0,0);
    lcd.print("Operation:");
    lcd.setCursor(0,1);
    while(Serial.available() > 0)
    {
      symbole = receptionOperation();
      lcd.clear();
    }
  }
  else
  {
    lcd.setCursor(0,0);
	if(symbole == '+')
    {
      float total = nombre1.toFloat() + nombre2.toFloat();
      lcd.print(total);
    }
    else if(symbole == '-')
    {
      float total = nombre1.toFloat() - nombre2.toFloat();
      lcd.print(total);
    }
    else if(symbole == '*')
    {
      float total = nombre1.toFloat() * nombre2.toFloat();
      lcd.print(total);
    }
    else if(symbole == '/')
    {
      if(nombre1.toFloat() == 0 || nombre2.toFloat() == 0)
      {
        lcd.print("Impossible de");
        lcd.setCursor(0,1);
        lcd.print("diviser par 0");
      }
      else
      {
        float total = nombre1.toFloat() / nombre2.toFloat();
        lcd.print(total);
      }
    }
    else
    {
      lcd.print("Mauvaise");
      lcd.setCursor(0,1);
      lcd.print("Operation");
    }
  }
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
  calculatrice();
}
```
