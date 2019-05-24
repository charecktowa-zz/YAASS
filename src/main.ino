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

/*For Fingerprint*/
#include <Adafruit_Fingerprint.h>
#include "fingerprint.hpp"

#include <SoftwareSerial.h>

#include <Servo.h>


/*For writting into the SD card*/
#include <SPI.h>
#include <SD.h>
#include "sdcardconfig.hpp"

/*Variables for the door system*/
byte newFP = 10;
byte checkFP = 11;
byte closeDoor = 13;
byte LED = 13;

bool opened_door = false;
bool closed_door = true;

Servo myServo;
int ServoPin = 6;

int DOOR_OPEN = 180;
int DOOR_CLOSED = 0;

bool thereisnoFP = false;

/*If the door is already open it will display a message saying
  it is already open, ifn't it will open the door*/
void door_open(){
  /*Checks if the door is opened*/
  if(opened_door == false){

    Serial.println("Abriendo la puerta.");

    for(int i = 0; i <= DOOR_OPEN; i++){
      myServo.write(i);
      delay(25);
    }
  } 
  else {
    Serial.println("La puerta ya está abierta.");
  }

}
void close_door(){
  if(closed_door == true){
    Serial.println("La puerta ya está cerrada");
  }
  else{
    for (int i = DOOR_OPEN; i >= DOOR_CLOSED; i--){
      myServo.write(i);
      delay(25);
    }
    
  }
  
}

void setup() {
  /*Sets the pins for the menu*/
  pinMode(newFP, INPUT);
  pinMode(checkFP, INPUT);
  pinMode(LED, OUTPUT);

  Serial.begin(9600);
  delay(100);

  initSDcard();

  Serial.println("\nInitializing fingerprint sensor...\n");
  finger.begin(57600);

  Fingerprintcheck();

  finger.getTemplateCount();
  Serial.print("El sensor tine: ");
  Serial.print(finger.templateCount); Serial.println(" huellas");


  if (finger.templateCount == 0) {
    Serial.println("\nNo hay huellas.");
    Serial.println("Agregando huella maestra...");
    thereisnoFP = true;
  }

  /*Starts the Servo*/
  myServo.attach(ServoPin);
  myServo.write(0);
}

void loop () {
  /*If there is no fingerprints into the sensor
    it will send the user automatically into the adding
    fingerprint option*/
  if (digitalRead(newFP) == HIGH || thereisnoFP == true) {
    delay(100);
    Serial.println("Listo para agregar la huella!");
    Serial.println("Por favor ingrese el ID # (DE 1 A 127)");
    id = readnumber();

    if (id == 0) {
      return;
    }

    Serial.print("Agregando ID #");
    Serial.println(id);

    while (!  getFingerprintEnroll());
    delay(100);
  }
  /*Checks the fingerprint,*/
  if (digitalRead(checkFP) == HIGH) {

    /*I don't know it works but it does
      don't change anything because I don't know
      how to fix it*/
    for (int i = 0; i < 50; i++) {
      getFingerprintIDez();
    }


    int confidence = finger.confidence;
    if (confidence >= 50) {
      door_open();
    }
  }
}