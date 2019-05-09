/*Includes the Arduino functions for avr-gcc*/
#include <Arduino.h>

/*For Fingerprint*/
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial fingerSerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerSerial);

uint8_t id;
byte newFP = 10;
byte checkFP = 11;

uint8_t readnumber(void) {
    uint num = 0;

    while (num == 0){
        while(!Serial.available());
        num = Serial.parseInt();
    }
    return num;
}

uint8_t getFingerprintEnroll() {
    int p = -1;
    Serial.prinln("Esperando un dedo valido para agregar");
    while (p != FINGERPRINT_OK)
    {
        p = finger.getImage();

        switch (p) {
            case FINGERPRINT_OK:
            Serial.println("Imagen obtenida");
            break;

            case FINGERPRINT_PACKETRECIEVEERR:
            Serial.prinln("Error de comunicación");
            break;

            case
        }
    }
    
}

void setup() {

    pinMode(newFP, INPUT);
    pinMode(checkFP, INPUT)

    Serial.begin(9600);
    while(!serial);
    delay(100);
    Serial.println("\nInicializando lector de huellas...\n");

    finger.begin(57600);

    if (finger.verifyPassword()) {
        Serial.println("Se ha encontrado el sensor!");
    } 
    else {
        Serial.println("No se ha encontrado algun sensor!\n");
        while(1) {delay(1);}
    }

    if 
}

void loop () {
    if (digitalRead(newFP) == 1) {
        Serial.println("Listo para agregar la huella!");
        Serial.println("Por favor ingrese el ID # (DE 1 A 127");

        if(id < 1 || id > 127)
            return;

        Serial.print("Agregando ID #")
        Serial.println(id);

        while (!getFingerprintEnroll());
    }
}