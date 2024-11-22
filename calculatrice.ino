```C++
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Création d'un objet LCD avec l'adresse I2C de l'écran
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Initialisation et affectation des variables globales
String nb1 = ""; // nb1 vide
String nb2 = ""; // nb2 vide
char symbole = '\0'; // symbole vide (\0)

//Fonction de reception du chiffre
String receptionChiffre()
{
  String message = ""; // Variable vide
  bool messageinvalide = true; // Initialisation et déclaration d'un bool en true

  do 
  {
    if (Serial.available()) // S'il y a quelque chose dans le buffer 
    {
      message = Serial.readStringUntil('\n'); // On lit jusqu'à la fin (\n) et on affecte la chaine de caracetere a message
      messageinvalide = false; // On met le bool à false de base

      int i = 0; // variable pour parcourir
      while (i < message.length() && messageinvalide == false) // Boucle à deux conditions, selon la taille du message et si le message est invalide
      {
        char c = message[i]; // on declare un char et on lui affecte la valeur de message[i], message[0] sera le premier caractere de la chaine
        if ((c < '0' || c > '9') && c != '.') // Condition si le caractere n'est pas entre 0 et 9 et qu'il ne s'agit pas d'un point
        {
          messageinvalide = true; // on met le bool à true
        }
        i++;
      }
    }
  } while (messageinvalide == true); // on fait tout ce qu'on fait précédement tant que le bool est à true, il ne l'est pas uniquement quand il s'agit d'un chiffre correct

  return message; // on retourne la valeur de message sous forme d'un string
}

// Fonction de reception de l'opération
char receptionOperation() 
{
  char operation = Serial.read(); // on declare un char et on lui affecte ce que l'utilisateur va entrer
  return operation; // on retourne la valeur de operation
}
//Fonction bool renvoyant false ou true selon si l'utilisateur veut refaire un calcul ou pas
bool nouvelleOperation()
{
  // on demande si il veut faire une nouvelle operation
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nouv. Oper. ?");
  lcd.setCursor(0, 1);
  lcd.print("(y/n)");
  
  char reponseUtilisateur; // declaration d'un char qui prendra le caractere entré par l'utilisateur

  while (reponseUtilisateur != 'y' && reponseUtilisateur != 'n') // on boucle tant que le caractere entré n'est pas y et n
  {
    if (Serial.available()) // S'il y a quelque chose dans le buffer
    {
      reponseUtilisateur = Serial.read(); // On affecte a notre char ce qu'à entrer l'utilisateur
      if (reponseUtilisateur == 'y') // Si c'est 'y'
      {
        return true; // On envoie true comme retour
      }
      else if (reponseUtilisateur == 'n') // Sinon si c'est 'n'
      {
        lcd.clear(); // on clear tout
        lcd.noBacklight(); // on enleve la lumiere de l'écran
      }
      else // si ce n'est ni 'y' ni 'n', on dit que ce n'est pas un bon choix et on redemande
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Mauv. Choix");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Nouv. Oper. ? (y/n)");
      }
    }
  }
}

// Fonction void qui ne renverra rien (fonction principale du programme)
void calculatrice()
{
  if(nb1 == "" && nb2 == "") // Si nb1 et nb2 n'ont aucune valeur affectée
  {
    lcd.setCursor(0,0);
    lcd.print("1er nombre:"); // On demande le premier nombre
    lcd.setCursor(0,1);
    // On affecte la valeur de retour de receptionChiffre() à nb1 qui est notre premier nombre puis on efface l'écran
    while(Serial.available() > 0) 
    {
      nb1 = receptionChiffre();
      lcd.clear();
    }
  }
  else if(nb1 != "" && nb2 == "") // Sinon si nb1 a une valeur mais que nb2 n'en a pas
  {
    lcd.setCursor(0,0);
    lcd.print("2eme nombre:"); // On demande le deuxieme chiffre
    lcd.setCursor(0,1);
    // On affecte la valeur de retour de receptionChiffre() à nb2 qui est notre deuxieme nombre puis on efface l'écran 
    while(Serial.available() > 0)
    {
      nb2 = receptionChiffre();
      lcd.clear();
    }
  }
  else if(nb1 != "" && nb2 != "" && symbole == '\0') // Sinon si nb1 et nb2 ont une valeur mais que symbole n'en a pas
  {
    lcd.setCursor(0,0);
    lcd.print("Operation:"); // On demande l'operation voulue
    lcd.setCursor(0,1);
    // On affecte la valeur de retour de receptionOperation() à symbole qui est notre symbole pour l'opération puis on efface l'écran
    while(Serial.available() > 0)
    {
      symbole = receptionOperation();
      lcd.clear();
    }
  }
  else // Si toutes les autres conditions sont remplis
  {
    float total = 0; // On declare un float qui contiendra le résultat du calcul
    lcd.setCursor(0,0);
	if(symbole == '+') // Si le symbole a comme caractère '+'
    {
      total = nb1.toFloat() + nb2.toFloat(); // On effectue une addition, on affecte la valeur de l'addition de nb1 et nb2 transformé en float (toFloat()) à total
      lcd.print(total); // on envoie le résultat
    }
    else if(symbole == '-') // Si le symbole a comme caractère '-'
    {
      total = nb1.toFloat() - nb2.toFloat(); // On effectue une soustraction, on affecte la valeur de la soustraction de nb1 et nb2 transformé en float (toFloat()) à total
      lcd.print(total); // on envoie le résultat
    }
    else if(symbole == '*') // Si le symbole a comme caractère '*'
    {
      total = nb1.toFloat() * nb2.toFloat(); // On effectue une multiplication, on affecte la valeur de la multiplication de nb1 et nb2 transformé en float (toFloat()) à total
      lcd.print(total); // on envoie le résultat
    }
    else if(symbole == '/') // Si le symbole a comme caractère '/'
    {
      if(nb1.toFloat() == 0 || nb2.toFloat() == 0) // Condition pour interdire une division par 0, si nb1 = 0 ou nb2 = 0 par exemple
      {
        lcd.print("Impossible de");
        lcd.setCursor(0,1);
        lcd.print("diviser par 0");
      }
      else
      {
        total = nb1.toFloat() / nb2.toFloat(); // On effectue une division, on affecte la valeur de la division de nb1 et nb2 transformé en float (toFloat()) à total
        lcd.print(total); // on envoie le résultat
      }
    }
    else // Si le symbole de l'opération n'est pas parmis les 4, on envoie a l'utilisateur qu'il a entré une mauvaise operation
    {
      lcd.print("Mauvaise");
      lcd.setCursor(0,1);
      lcd.print("Operation");
    }
    // On attend 5s le temps que l'utilisateur lise le résultat
    delay(5000);
    if(nouvelleOperation() == true) // On appel nouvelleOperation, et si l'utilisateur entre 'y' alors on vide les variables et on efface l'écran.
    {
      nb1 = "";
      nb2 = "";
      symbole = '\0';
      lcd.clear();
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
  calculatrice(); // On a juste a appeler cette fonction dans le loop pour que le programme commence
}
```
