```C++
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
String choix1, choix2;
String operation[] = { "*", "+", "-","/" };
String valide[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "."};
bool commandeTrouvee = false;


void setup()
{
    lcd.begin(16, 2);
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);

}

void saisie() { 
  while(commandeTrouvee == false){
    lcd.setCursor(0, 0);
    lcd.print("Saisir un nombre");
    lcd.setCursor(0, 1);
    lcd.print("!");
    verifnombre();
    delay(1000);
  
  }
  
  lcd.print(choix1);
  
    //verifoperation();
}

void verifnombre(){
	String choix = "";
    while (Serial.available() > 0) {
      char receivedChar = Serial.read();
      choix = receivedChar;
      
      
      if (choix.length() > 0) {
        int i = 0;
        while (i < 11) {
            if (valide[i] == choix) {
               
              calcul(i);
                commandeTrouvee = true;
               	
              	choix1 += receivedChar;
     
            }
            i++;
        }

        if (!commandeTrouvee) {
            lcd.print("Commande inconnue");
          	
        }
    }
      
    }
    
 	
}


/*void verifoperation() {
    String choix = "";
    while (Serial.available() > 0) {
        char receivedChar = Serial.read();
        choix += receivedChar;
        delay(100);
    }
    if (choix.length() > 0) {
        int i = 0;
        bool commandeTrouvee = false;

        while (i < 4) {
            if (operation[i] == choix) {
                calcul(i);
                commandeTrouvee = true;
            }
            i++;
        }

        if (!commandeTrouvee) {
            lcd.print("Commande inconnue");
        }
    }


}*/

void calcul(int ope){

lcd.print("GG");
}

void loop()
{
    saisie();
}
```
