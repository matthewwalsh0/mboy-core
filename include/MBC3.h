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
    u_int8_t romBank = 1;
    int16_t ramBank = 1;
public:
    int16_t get_8(u_int16_t address, u_int8_t* rom, Ram* ram);
    bool set_8(u_int16_t address, u_int8_t value, u_int8_t* rom, Ram* ram);
};

#endif //MBOY_ANDROID_MBC3_H
