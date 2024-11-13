// C++ code
//
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);
int n_1;
int n_2;
char op;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
}

void 1_nombre()
{
  Wire.beginTransmission(0x20);
  int buffer = Serial.available();
  char c;
  String s = "";
  while(buffer > 0)
  {
    c = Serial.read();
    s += c;
  }
  n_1 = s.toInt();
  Wire.write(s);
  Wire.endTransmission();
}

void 2_nombre()
{
  Wire.beginTransmission(0x20);
  int buffer = Serial.available();
  char c;
  String s = "";
  while(buffer > 0)
  {
    c = Serial.read();
    s += c;
  }
  n_2 = s.toInt();
  Wire.write(s);
  Wire.endTransmission;
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
  Wire.write(c);
  Wire.endTransmission;
}

void calcul()
{
  int res;
  switch (op)
  {
    case '+':
    {
      res = n_1 + n_2;
      break;
    }
    case '-':
    {
      res = n_1 - n_2;
      break;
    }
    case '*':
    {
      res = n_1 * n_2;
      break;
    }
    case '/':
    {
      res = n_1 / n_2;
      break;
    }
  }
}
void loop()
{
  1_nombre();
  2_nombre();
  operateur();
  calcul();
}
