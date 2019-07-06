/***************************************************
  This is an example sketch for our optical Fingerprint sensor
  Designed specifically to work with the Adafruit Fingerprint sensor
  ----> http://www.adafruit.com/products/751
  These displays use TTL Serial to communicate, 2 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "fingerprint.hpp"
#include <stdint.h>

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerSerial);
uint8_t id;


/*reads the number for the ID*/
uint8_t readnumber(void) 
{

    uint8_t num = 0;

    while (num == 0) {
        while (!Serial.available());
        num = Serial.parseInt();
    }
    return num;
}

/**/
uint8_t getFingerprintEnroll() 
{

    int p = -1;
    Serial.print(F("Esperando dedo valido #")); Serial.println(id);
    while (p != FINGERPRINT_OK) {
        p = finger.getImage();
        switch (p) {
            case FINGERPRINT_OK:
                Serial.println(F("Imagen tomada"));
                break;
            case FINGERPRINT_NOFINGER:
                Serial.println(".");
                break;
            case FINGERPRINT_PACKETRECIEVEERR:
                Serial.println(F("Error de comunicacion"));
                break;
            case FINGERPRINT_IMAGEFAIL:
                Serial.println(F("Error de imagen"));
                break;
            default:
                Serial.println(F("Error desconocido"));
                break;
        }
    }

    // OK success!

    p = finger.image2Tz(1);
    switch (p) {
        case FINGERPRINT_OK:
            Serial.println(F("Imagen añadida"));
            break;
        case FINGERPRINT_IMAGEMESS:
            Serial.println(F("Imagen de baja calidad"));
            return p;
        case FINGERPRINT_PACKETRECIEVEERR:
            Serial.println(F("Error de comunicación"));
            return p;
        case FINGERPRINT_FEATUREFAIL:
            Serial.println(F("No se encontró huella valida"));
            return p;
        case FINGERPRINT_INVALIDIMAGE:
            Serial.println(F("No se pudo encontrar una imagen valida"));
            return p;
        default:
            Serial.println(F("Error desconocidos"));
            return p;
    }

    Serial.println(F("Retire el dedo"));
    delay(2000);
    p = 0;
    while (p != FINGERPRINT_NOFINGER) {
        p = finger.getImage();
    }
    Serial.print("ID "); Serial.println(id);
    p = -1;
    Serial.println(F("Coloque otra vez el mismo dedo"));
    while (p != FINGERPRINT_OK) {
        p = finger.getImage();
        switch (p) {
            case FINGERPRINT_OK:
                Serial.println(F("Imagen tomada"));
                break;
            case FINGERPRINT_NOFINGER:
                Serial.print(".");
                break;
            case FINGERPRINT_PACKETRECIEVEERR:
                Serial.println(F("Error de comunicasancia"));
                break;
            case FINGERPRINT_IMAGEFAIL:
                Serial.println(F("Imagen erronea"));
                break;
            default:
                Serial.println(F("Error desconocido"));
                break;
        }
    }

    // OK success!

    p = finger.image2Tz(2);
    switch (p) {
        case FINGERPRINT_OK:
            Serial.println(F("Imagen convertida"));
            break;
        case FINGERPRINT_IMAGEMESS:
            Serial.println(F("Imagen toda fea"));
            return p;
        case FINGERPRINT_PACKETRECIEVEERR:
            Serial.println(F("Error de comunicacion"));
            return p;
        case FINGERPRINT_FEATUREFAIL:
            Serial.println(F("No se encontró una huella"));
            return p;
        case FINGERPRINT_INVALIDIMAGE:
            Serial.println(F("Imagen invalida"));
            return p;
        default:
            Serial.println(F("Error desconocido"));
            return p;
    }

    // OK converted!
    Serial.print(F("Creando modelo #")); Serial.println(id);

    p = finger.createModel();
    if (p == FINGERPRINT_OK) {
        Serial.println(F("Huellas encontrados!"));
    } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
        Serial.println(F("Error de comunicación"));
        return p;
    } else if (p == FINGERPRINT_ENROLLMISMATCH) {
        Serial.println(F("No se encontraron coincidencia"));
        return p;
    } else {
        Serial.println(F("Error desconocido"));
        return p;
    }

    Serial.print("ID "); Serial.println(id);
    p = finger.storeModel(id);
    if (p == FINGERPRINT_OK) {
        Serial.println(F("Guardado!"));
    } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
        Serial.println(F("Error de comunicación"));
        return p;
    } else if (p == FINGERPRINT_BADLOCATION) {
        Serial.println(F("No se alcanzó esa posición de memoria"));
        return p;
    } else if (p == FINGERPRINT_FLASHERR) {
        Serial.println(F("Error escribiendo en la memoria"));
        return p;
    } else {
        Serial.println(F("Error desconocodo"));
        return p;
    }
}

/* returns -1 if failed, otherwise returns ID # */
int getFingerprintIDez() 
{

    uint8_t p = finger.getImage();
    if (p != FINGERPRINT_OK) return -1;

    p = finger.image2Tz();
    if (p != FINGERPRINT_OK) return -1;

    p = finger.fingerFastSearch();
    if (p != FINGERPRINT_OK) return -1;

    // found a match!
    Serial.print(F("Found ID #")); Serial.print(finger.fingerID);
    Serial.print(F(" with confidence of ")); Serial.println(finger.confidence);
    return finger.fingerID;
}

/*This function checks if the fingerprint sensor
  is available*/
void initFPS() 
{
    Serial.println(F("Intentando inicializar sensor de huellas..."));
    finger.begin(57600);
    while (finger.verifyPassword() == false) 
    {
        if (finger.verifyPassword() == true){
            Serial.println("Sensor incializado correctamente");
            delay(1000);
        } else {
            Serial.println("No se ha encontrado el sensor");
            delay(1000);
        }
    }
    Serial.println("Sensor incializado correctamente");
    delay(1000);
}