// C++ code
//
//#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);
float premier_nombre;
float deuxieme_nombre;
char op;
String resultat= "";
int wait;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
}

void saisir_nombre()
{
  Wire.beginTransmission(0x20);
  int buffer = Serial.available();
  char c;
  String s = "";
  while(buffer > 0)
  {
    c = Serial.read();
    s += c;
    buffer = Serial.available();
  }
  //Wire.write(s);
  Wire.endTransmission();
  if(premier_nombre != 0.0)
    deuxieme_nombre = s.toFloat();
  else
    premier_nombre = s.toFloat();
  wait += 1;
}

void operateur()
{
  Wire.beginTransmission(0x20);
  int buffer = Serial.available();
  char c;
  while(buffer > 0)
  {
    c = Serial.read();
  }
  op = c;
  //Wire.write(op);
  Wire.endTransmission();
  wait += 1;
}

void calcul()
{
  Wire.beginTransmission(0x20);
  switch (op)
  {
    case '+':
    {
      resultat = String(premier_nombre + deuxieme_nombre);
      break;
    }
    case '-':
    {
      resultat = String(premier_nombre - deuxieme_nombre);
      break;
    }
    case '*':
    {
      resultat = String(premier_nombre * deuxieme_nombre);
      break;
    }
    case '/':
    {
      resultat = String(premier_nombre / deuxieme_nombre);
      break;
    }
  }
  //Wire.write(resultat);
  Wire.endTransmission();
}

void loop()
{
  if (wait == 0)
  	saisir_nombre();
  if (wait == 1)
  	operateur();
  if (wait == 2)
  	saisir_nombre();
  if (wait == 3)
  	calcul();
}
