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


#ifndef _fingerprint_h
#define _fingerprint_h

#include <Arduino.h>
#include <stdint.h>

#include <Adafruit_Fingerprint.h>

uint8_t readnumber(void); /*Reads the number for the ID of the fingerprint image*/
uint8_t getFingerprintEnroll()
uint8_t getFingerprintID()
int getFingerprintIDez()

#endif
