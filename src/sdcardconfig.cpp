#include "sdcardconfig.hpp"
#include <stdint.h>

File myFile;
/*I don't have a really good name for the log file*/
String FILE_NAME_LOG = "cochinita.log";

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
    myFile = SD.open(FILE_NAME_LOG, FILE_WRITE);
}
