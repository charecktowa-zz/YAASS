#ifndef _sdcardconfig_hpp
#define _sdcardconfig_hpp

#include <Arduino.h>
#include <stdint.h>

#include <SPI.h>
#include <SD.h>

File VAPCIII;
/*I don't have a really good name for the log file*/
String FILE_NAME_LOG = "cochinita.log" 


void initSDcard();
#endif