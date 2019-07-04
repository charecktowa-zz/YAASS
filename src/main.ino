
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

#include <SD.h>
#include <SPI.h>
#include "libraries/sdcardconfig.hpp"

#include <Adafruit_Fingerprint.h>
#include "libraries/fingerprint.hpp"

#include <Wire.h>
//#include <LiquidCrystal_I2C.h>

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

  Serial.begin(57600); //bauds
  //initSDcard();
  fingerprintcheck();

  /*Begins to check if exist templates on the fingerprint sensor*/
  finger.getTemplateCount();
  Serial.print("El sensor tiene: "); 
  Serial.print(finger.templateCount); Serial.println("huellas");

  if (finger.templateCount == 0) {
    Serial.println("\nNo existen huellas");
    Serial.println("Agregando huella maestra...");
    thereisnoFP = true;

    while (thereisnoFP == true) {
      Serial.println("Inserte su dedo dentro del sensor de huellas");
      delay(100);
      id = main_user_id;

      while (!getFingerprintEnroll());
      Serial.println("Huella maestra agregada exitosamente.");
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
    id_add = true;
    counter = 0;
    while ( (main_user_exist == true && counter < 3) || (id_add == true) )
    {
      Serial.println("Ingrese la huella maestra.");
      user_id = getFingerprintIDez();
      delay(100);

      if (user_id == main_user_id) {
        Serial.println("Las huellas coinciden");
        delay(500);

        /*Adds a new fingerprint*/
        Serial.println("Listo para agregar huella!");
        Serial.println("Por favor ingrese un ID # (2 - 127)");

        /*Need to change how to recibe an input number*/
        id = -1;
        id = readnumber();
        if (id == 0 || id == 1) {
          Serial.println("ID no valido.");
          counter++;
        }

        Serial.print("Agregando ID #");
        Serial.println(user_id);

        while (! getFingerprintEnroll() );
        id_add = false;        
      }

      if (user_id != main_user_id) {
        if (user_id == -1){
          Serial.println("Error leyendo la huella.");
          counter++;
        }
        /* I don't know why (yet) but when the fingerprint
           does not have an input, the function returns 255
           If there is not a finger in the sensor the program
           will not do something*/
        else if (user_id == 255) {
          Serial.println("Esperando huella valida.");
          donothing();
        }
        /* If the function recives a valid fingerprint but
           it's not the the "main" finger will report it */
        else {
          Serial.println("Ingrese unicamente la huella maestra");
          counter++;
          // should report this to the SD card
        }
          delay(1000);
        }
      }
}

  if (digitalRead(checkFP == HIGH)) {
    Serial.println("Ingrese una huella para abrir la puerta.");

    counter = 0;
    user_id = -1;
    while (door_closed == false && counter < 3)
    {
      Serial.println("Esperando huella");
      user_id = getFingerprintIDez();
      delay(100);
      Serial.println("ID recibido: "); Serial.println(user_id);

      /* Because the 1 is the main user ID and 127 is the max ID available */
      if (user_id > 1 && user_id < 127) {
        /*Does the servo stuff*/
      }

      else if (user_id == -1) {
        Serial.println("Error leyendo huella.");
        counter++;
      }

      else {
        donothing();
      }
    }
  }
}