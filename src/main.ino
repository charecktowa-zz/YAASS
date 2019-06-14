
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
#include "sdcardconfig.hpp"

#include <Adafruit_Fingerprint.h>
#include "fingerprint.hpp"

byte newFP = 10;
byte checkFP = 11;

uint8_t main_user_id = 1;
uint8_t user_id;

bool thereisnoFP = false;
bool main_user_exist = false;

void setup () {
  /* Set the pin for the main menu */
  pinMode(newFP, INPUT);
  pinMode(checkFP, INPUT);
  /*pinMode(); */

  Serial.begin(9600); //bauds
  initSDcard();
  fingerprintcheck();

  /*Begins to check if exist templates on the fingerprint sensor*/
  finger.getTemplateCount();
  Serial.print("El sensor tiene: "); 
  Serial.println(finger.templateCount); Serial.println("huellas");

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

}

void loop () {
  if (digitalRead(newFP) == HIGH) {
    byte counter = 0;
    while (main_user_exist == true && counter >= 3) {
      Serial.println("Inserte huella maestra");
      delay(100);
      user_id = getFingerprintID();

      if (user_id != main_user_id)
        counter++;

      else if (user_id == main_user_id) {
        Serial.println("Listo para agregar la huella");
        Serial.println("Ingrese el ID ");

        id = readnumber();

        if (id == 0){
          Serial.println("El ID # 0 no es un valor valido");
        }

        Serial.println("Agregando ID #");
        Serial.print(id);

        while (! getFingerprintEnroll());
        delay(100);
      }
    
    }
  }

  if (digitalRead(checkFP == HIGH)) {}
}