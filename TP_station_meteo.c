// C++ code
//

#include <Wire.h>
#include <LiquidCrystal_I2C.h>



// Création d'un objet LCD avec l'adresse I2C de l'écran
LiquidCrystal_I2C lcd(0x27, 16, 2);
float humidite = 0;
int temperature = 0;
float hisimp = 0;
float hicomp = 0;


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

float calculateHeatIndex(float temperature, float humidite) {
  return -42.379 +
         2.04901523 * temperature +
         10.14333127 * humidite -
         0.22475541 * temperature * humidite -
         0.00683783 * temperature * temperature -
         0.05481717 * humidite * humidite +
         0.00122874 * temperature * temperature * humidite +
         0.00085282 * temperature * humidite * humidite -
         0.00000199 * temperature * temperature * humidite * humidite;
}

void loop()
{
  humidite = (float)analogRead(A3)/876;
  temperature = round(analogRead(A2)*(5.0/1024.0)*100-50)*9/5+32;
  
  hisimp = 0.5 * (temperature + 61.0 + ((temperature-68.0)*1.2) + (humidite*0.094));
  hicomp = calculateHeatIndex(temperature, humidite);
  Serial.println(humidite);
  lcd.setCursor(0,0);
  lcd.print("hiSimp : ");
  lcd.print(hisimp);
  lcd.print(" F     ");
  lcd.setCursor(0,1);
  lcd.print("hicomp : ");
  lcd.print(hicomp);
  lcd.print(" F   ");
  delay(200); 
}
