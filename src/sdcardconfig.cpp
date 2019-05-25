#include "sdcardconfig.hpp"
#include <stdint.h>

File myFile;
/*I don't have a really good name for the log file*/

void initSDcard(){

    Serial.println("Inicializando la tarjeta SD.");

    if(!SD.begin(53)){
        Serial.println("Error inicializando.");
        while(1);
    }

    Serial.println("Inicialización correcta.");

    if(SD.exists("cochinita.log")){
        Serial.println("El archivo log ya existe.");
    }
    else {
        Serial.println("El archivo log no existe.");
    }

    Serial.println("Creando archivo log.");
    myFile = SD.open("cochinita.log", FILE_WRITE);
}
