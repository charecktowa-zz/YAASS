
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

#include <Arduino.h>

#include <Adafruit_Fingerprint.h>
#include "fingerprint.hpp"

const byte newFP = 10;
const byte checkFP = 13;

const uint8_t main_user_id = 1;
uint8_t user_id = -1; 

/*For checking the while loop*/
bool thereisnoFP = false;
bool main_user_exist = false;
bool id_add = false;
bool door_closed = false;
byte counter = 0; 

void setup () {
  /* Set the pin for the main menu */
  pinMode(newFP, INPUT);
  pinMode(checkFP, INPUT);
  /*pinMode(); */

  Serial.begin(9600); //bauds
  //initSDcard();
  initFPS();

  /*Begins to check if exist templates on the fingerprint sensor*/
  finger.getTemplateCount();
  Serial.print(F("El sensor tiene")); 
  Serial.print(finger.templateCount); Serial.println(F("huellas"));

  if (finger.templateCount == 0) {
    Serial.println(F("\nNo se encontraron huellas"));
    delay(1000);
    Serial.println(F("Añadiendo huella maestra"));
    thereisnoFP = true;

    while (thereisnoFP == true) 
    {
      Serial.println(F("Coloque el dedo sobre el sensor"));
      delay(100);
      id = main_user_id;

      while (!getFingerprintEnroll());
      Serial.println(F("Huella añadida correctamente."));
      main_user_exist = true;
      thereisnoFP = false;
    }
  }

  else {
    main_user_exist = true;
  }

}

void loop () {
  if (digitalRead(newFP) == HIGH) {
    Serial.println(F("Agregar nueva huella"));
    delay(1000);
    id_add = true;
    counter = 0;
    while ( (main_user_exist == true && counter < 3) || (id_add == true) )
    {
      Serial.println(F("Coloque el dedo sobre el sensor"));
      user_id = getFingerprintIDez();
      delay(100);

      if (user_id == main_user_id) {
        Serial.println(F("¡Las huellas coinciden!"));
        delay(500);

        /*Adds a new fingerprint*/
        Serial.println(F("Listo para agregar huellas"));
        Serial.println(F("Ingrese un ID # (de 2 a 127)"));

        /*Need to change how to recibe an input number*/
        id = -1;
        id = readnumber();
        if (id == 0 || id == 1) {
          Serial.println(F("ID no valido"));
          counter++;
        }

        Serial.print(F("Agregando ID #"));
        Serial.println(user_id);

        while (! getFingerprintEnroll() );
        id_add = false;        
      }

      if (user_id != main_user_id) {
        if (user_id == -1){
          Serial.println(F("Las huellas no coinciden."));
          counter++;
        }
        /* I don't know why (yet) but when the fingerprint
           does not have an input, the function returns 255
           If there is not a finger in the sensor the program
           will not do something*/
        else if (user_id == 255) {
          Serial.println(F("Esperando una huella valida"));
          delay(1500);
        }
        /* If the function recives a valid fingerprint but
           it's not the the "main" finger will report it */
        else {
          Serial.println(F("Coloque únicamente la huella maestra"));
          counter++;
          // should report this to the SD card
        }
          delay(1000);
        }
      }
}

  if (digitalRead(checkFP == HIGH)) {
    Serial.println(F("Ingrese una huella para abrir la puerta."));
    delay(1000);
    counter = 0;
    user_id = -1;
    while (door_closed == false && counter < 3)
    {
      Serial.println(F("Esperando huella"));
      user_id = getFingerprintIDez();
      delay(100);
      Serial.println(F("ID recibido: ")); Serial.println(user_id);

      /* Because the 1 is the main user ID and 127 is the max ID available */
      if (user_id > 1 && user_id < 127) {
        /*Does the servo stuff*/
      }

      else if (user_id == -1) {
        Serial.println(F("Error leyendo huella."));
        counter++;
      }

      else {
        delay(1500);
      }
    }
  }
}