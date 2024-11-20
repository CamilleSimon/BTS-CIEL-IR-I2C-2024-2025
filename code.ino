// C++ code


#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// Création d'un objet LCD avec l'adresse I2C de l'écran
LiquidCrystal_I2C lcd(32, 16, 2);
int buff = 0;
String string1 = "";
String string2= "";
String string3= "";
int int1;
int int2;
int etape = 0;

void setup()
{
	
    lcd.begin(16,2);
    lcd.init();
    lcd.backlight();
	Serial.begin(9600);
}

void loop()
{	
  	lcd.setCursor(0, 1);
  	char readChar;
  	int buff = Serial.available();
  
  
  
  //ETAPE 0 --------------------------------
  
  	if (etape == 0 )
    {	
      	delay(500);
    	string1 = "";
      	string2 = "";
      	string3 = "";
      	etape = 1;
      	lcd.print("1er Nombre             ");
    
    }

  
  //ETAPE 1 ---------------------------------------
  
    if (etape == 1)
    {
      
      	
          
        while(buff > 0) // tant qu'il reste des caractères dans le buffer
        {	
            delay(10);
            readChar = Serial.read();
			
          	
          	
          
            string1 = string1 + readChar;
          	
            buff = Serial.available(); // mise à jour du nombre de caratères restant
        	
        }
      
       if (string1 != "")
        {
         	delay(10);
            for (int i = 0; i< string1.length() ; i++)
          	{

                if ( string1[i] < 48 || string1[i] > 57 )
                    {
                  		if (string1[i] == 46)
                        {
                        }
                  
                  		else 
                        {  
                          lcd.print("Erreur de nombre       ");
                          etape = 0;
                          string1 = "";
                        }
                    }

           		
              
         	}
         	
         
        }
      
      	if (string1 != "")
        {
          etape = 2;
          //Serial.print(string1);
          lcd.print("2e Nombre          ");
        }
      	
       
      	
    }

  
  	//ETAPE 2 ------------------------------------
  
  
    if (etape == 2)
    {
        while(buff > 0) // tant qu'il reste des caractères dans le buffer
        {	
            delay(10);
            readChar = Serial.read();

            string2 = string2 +readChar;
            buff = Serial.available(); // mise à jour du nombre de caratères restant
        }
      
      	if (string2 != "")
        {
         	delay(10);
          
            for (int i = 0; i< string2.length() ; i++)
          	{

                if ( string2[i] < 48 || string2[i] > 57 )
                    {
                  		if (string2[i] == 46)
                        {
                        }
                  
                  		else 
                        {  
                          lcd.print("Erreur de nombre      ");
                          etape = 0;
                          string2 = "";
                        }
                    }
              
              	
            }
          
          
   	 	}
      
      
        if (string2 != "")
          {
            etape = 3;
            //Serial.print(string1);
            lcd.print("Donnez l'operant        ");
          }

  
    }
  	//ETAPE 3 -------------------------------------
  
  
  
    if (etape == 3)
    {
        while(buff > 0) // tant qu'il reste des caractères dans le buffer
        {	
            delay(10);
            readChar = Serial.read();

            string3 = string3 +readChar;
            buff = Serial.available(); // mise à jour du nombre de caratères restant
        }
      
      	int final_char = string3[0];
      
      	if (string3 != "")
        {
          if (final_char ==43 || final_char ==45  || final_char ==42  || final_char ==47  )
          {

            etape+=1;
            //Serial.print(string3);

          }
          else
          {
              etape = 0;
              lcd.print("Mauvais operant");
          }
        }

    
	}
 
int final_char = string3[0];
  
  	//ETAPE 4 -----------------------
  

  
  	if (etape == 4)
    {
    	lcd.setCursor(0, 1);
      	float res1 = string1.toFloat();
        float res2 = string2.toFloat();
      
 //---------------- " + " ---------------------------
      	if (final_char == 43)
        {
          	float resultat = res1 +res2;
          	lcd.print(resultat);
          	delay(50);
          	lcd.print("                       ");
          	etape = 0;
          
        }
//---------------- " - " ---------------------------
      	if (final_char == 45)
        {
          	float resultat = res1 - res2;
          	lcd.print(resultat);
          	delay(50);
          	lcd.print("                       ");
          	etape = 0;
        }
      
 //---------------- " * " ---------------------------
      	if (final_char == 42)
        {
          	float resultat = res1 *res2;
          	lcd.print(resultat);
          	delay(50);
          	lcd.print("                       ");
          	etape = 0;
          
        }
 //---------------- " / " ---------------------------
        if (final_char == 47)
        {
          	if (string2 == "0")
            {
            	lcd.print("Division par 0");
              	etape = 0;
            }
          	else
            {
              float resultat = res1 / res2;
              lcd.print(resultat);
              delay(50);
              lcd.print("                       ");
              etape = 0;
            }
        }
     	
      		
          
        
    }
	
  
  	//Serial.print();


  
  delay(1000);
}
