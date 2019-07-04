#include "sdcardconfig.hpp"
#include <stdint.h>

File myFile;
/*I don't have a really good name for the log file*/

char logfile[15] = "cochinita.log";

void initSDcard(){

    Serial.println("Inicializando la tarjeta SD.");

    if(!SD.begin(53)){
        Serial.println("Error inicializando.");
        while(1);
    }

    Serial.println("Inicialización correcta.");

    if(SD.exists(logfile)){
        Serial.println("El archivo log ya existe.");
    }
    else {
        Serial.println("El archivo log no existe.");
    }

    Serial.println("Creando archivo log.");
    myFile = SD.open(logfile, FILE_WRITE);
}

void writetoSDcard(String Message){
    myFile.println(Message);
    myFile.close();
    Serial.println("Guardado en la SD.");
}