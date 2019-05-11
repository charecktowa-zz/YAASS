#include "servosettings.hpp"
#include <stdint.h>

void ServoInitialize(byte ServoPin) {
    Servo.attach(ServoPin);

    servoMotor.write(0);
    delay(1000);
}

/*Moves the Servo degree by degree*/

void OpenDoor() {
    for (int i = 0; i <= DOOR_OPEN; i++) {
        servoMotor.write(i)
        delay(25);
    }
}

void CloseDoor() {
    for (int j = DOOR_OPEN - 1; i >= DOOR_CLOSED; i--) {
        servoMotor.write(j);
        delay(25);
    }

}
