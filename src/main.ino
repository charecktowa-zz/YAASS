/*Includes the Arduino functions for avr-gcc*/
#include <Arduino.h>

/*For Fingerprint*/
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

#include <Servo.h>

Servo doorsys;
/* For Arduino Uno, Micro or similar you can use this for creating *
*  the TX / RX but in the Arduino Mega it is not necessary,        *
*/

SoftwareSerial fingerSerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerSerial);

uint8_t id;

/*Buttons for add, delete and close*/
byte scan_button = 13;
byte add_button = 12;
byte close_button = 11;

void setup () {
    Serial.begin(9600); 
    while (!Serial); /*Checks if the Serial port is available*/

    Serial.println("\n");

    pinMode(scan_button, INPUT);
    pinMode(add_button, INPUT);
    pinMode(close_button, INPUT);

}

void loop () {
    NewFP();
}