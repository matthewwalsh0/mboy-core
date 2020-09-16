//
// Created by matthew on 06/07/2020.
//

#ifndef MY_APPLICATION_GUI_H
#define MY_APPLICATION_GUI_H

#include "Types.h"

const u_int8_t BUTTON_START = 0;
const u_int8_t BUTTON_SELECT = 1;
const u_int8_t BUTTON_A = 2;
const u_int8_t BUTTON_B = 3;
const u_int8_t BUTTON_UP = 4;
const u_int8_t BUTTON_RIGHT = 5;
const u_int8_t BUTTON_DOWN = 6;
const u_int8_t BUTTON_LEFT = 7;

class GUI {
public:
    virtual bool isOpen() { return true; }
    virtual void displayBuffer(u_int32_t* pixels) {};
    virtual void displayFPS(u_int16_t fps) {};
    virtual bool isDown(u_int8_t button) { return false; }
    virtual void playAudio(float* samples, u_int16_t count) {};
};


#endif //MY_APPLICATION_GUI_H
