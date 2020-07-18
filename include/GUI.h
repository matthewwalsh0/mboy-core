//
// Created by matthew on 06/07/2020.
//

#ifndef MY_APPLICATION_GUI_H
#define MY_APPLICATION_GUI_H

#include "Types.h"

const uint8 BUTTON_START = 0;
const uint8 BUTTON_SELECT = 1;
const uint8 BUTTON_A = 2;
const uint8 BUTTON_B = 3;
const uint8 BUTTON_UP = 4;
const uint8 BUTTON_RIGHT = 5;
const uint8 BUTTON_DOWN = 6;
const uint8 BUTTON_LEFT = 7;

class GUI {
public:
    virtual bool isOpen() { return true; }
    virtual void displayBuffer(uint32* pixels) {};
    virtual void displayFPS(uint16 fps) {};
    virtual bool isDown(uint8 button) { return false; }
    virtual void playAudio(float* samples, uint16 count) {};
};


#endif //MY_APPLICATION_GUI_H
