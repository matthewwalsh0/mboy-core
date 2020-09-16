#ifndef MBOY_ANDROID_JOYPAD_H
#define MBOY_ANDROID_JOYPAD_H

#include "Types.h"

#include "GUI.h"
#include "Memory.h"

class Joypad {
private:
    u_int8_t column = 0;
    GUI* gui;
public:
    Joypad(GUI* gui, Memory* memory);
};

#endif //MBOY_ANDROID_JOYPAD_H
