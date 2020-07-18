//
// Created by matthew on 17/07/2020.
//

#ifndef MBOY_ANDROID_JOYPAD_H
#define MBOY_ANDROID_JOYPAD_H

#include "Types.h"
#include "GUI.h"
#include "MemoryHook.h"

class Joypad : MemoryHook {
private:
    uint8 column = 0;
    GUI* gui;
public:
    Joypad(GUI* gui);
    uint8 get_8(uint16 address);
    bool set_8(uint16 address, uint8 value);
};

#endif //MBOY_ANDROID_JOYPAD_H
