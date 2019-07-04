#include <Arduino.h>
#include <stdint.h>

#include "servomotor.hpp"

const byte servoPin = 6;
const uint16_t pulseStart = 500;
const uint8_t pulseOpen = 0;
const uint8_t pulseClose = 0;

void initServo(){
    Serial.println("Inicializando Servo Motor");
    pinMode(servoPin, OUTPUT);

    digitalWrite(servoPin, HIGH);
    delayMicroseconds(pulseStart);
    digitalWrite(servoPin, LOW);
}