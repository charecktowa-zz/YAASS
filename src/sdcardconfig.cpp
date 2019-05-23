#include "sdcardconfig.hpp"
#include <stdint.h>

void initSDcard(){

    Serial.println("Inicializando la tarjeta SD.");

    if(!SD.begin(53)){
        Serial.println("Error inicializando.");
        while(1);
    }

    Serial.println("Inicialización correcta.");

    if(SD.exists(FILE_NAME_LOG)){
        Serial.println("El archivo log ya existe.");
    }
    else {
        Serial.println("El archivo log no existe.");
    }

    Serial.println("Creando archivo log.");
    VAPCIII = SD.open(FILE_NAME_LOG, FILE_WRITE);
}
