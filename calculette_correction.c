#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
float nb1,nb2;
char operateur;

float valid (String s)
{
  bool caracInvalid = false;
  do{
    lcd.print(s);
    String entreUtilisateur = "";
    if(Serial.available())
    {
      entreUtilisateur = Serial.readUntil("\n");
    }
    int i = 0;
    while (i<entreUtilisateur.leath() ){
      int c = entreUtilisateur[i];
      if ((c < 48 // c > 57) && c != 46)
        caracInvalid = true;
      i++;
    }while(caracInvalid == true);

    return entreUtilisateur.toFloat();  
  }
}

void loop()
{
  nb1 = valid("Entrez le premier nombre:")
  nb2 = valid("Entrez le deuxieme nombre:")
  
}

