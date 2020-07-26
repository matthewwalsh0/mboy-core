//
// Created by matthew on 18/07/2020.
//

#ifndef MBOY_ANDROID_MBC3_H
#define MBOY_ANDROID_MBC3_H

#include "Types.h"
#include "MemoryHook.h"
#include "Rom.h"

class MBC3 : Controller {
private:
    bool ramEnabled = false;
    uint8 romBank = 1;
    int16 ramBank = 1;
public:
    int16 get_8(uint16 address, uint8* rom, uint8* ram);
    bool set_8(uint16 address, uint8 value, uint8* rom, uint8* ram);
};

#endif //MBOY_ANDROID_MBC3_H
