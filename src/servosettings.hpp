/*
    For this project you can change the Servo for other system to open the door
    In this case it will be used the Servo because it is more easy to use and cheaper
    but it is better to use a more "safer" system
*/

#ifndef _servosettings_hpp
#define _servosettings_hpp

#include <Arduino.h>
#include <stdint.h>

#include <Servo.h>

const int DOOR_OPEN = 180 /*You can change the degrees as you need*/
#define DOOR_CLOSED

    void ServoInitialize(byte ServoPin);
    void OpenDoor();
    void close_door();

#endif
