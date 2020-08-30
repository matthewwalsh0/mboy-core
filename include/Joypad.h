//
// Created by matthew on 17/07/2020.
//

#ifndef MBOY_ANDROID_JOYPAD_H
#define MBOY_ANDROID_JOYPAD_H

#include <sys/types.h>
#include "GUI.h"
#include "MemoryHook.h"

class Joypad : MemoryHook {
private:
    u_int8_t column = 0;
    GUI* gui;
public:
    Joypad(GUI* gui);
    u_int8_t get_8(u_int16_t address);
    bool set_8(u_int16_t address, u_int8_t value);
};

#endif //MBOY_ANDROID_JOYPAD_H
