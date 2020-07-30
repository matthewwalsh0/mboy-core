//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_MEMORYHOOK_H
#define MY_APPLICATION_MEMORYHOOK_H

#include "Types.h"

class MemoryHook {
public:
    virtual uint8 get_8(uint16 address) {
        return 0;
    }

    virtual uint8 getHDMA(uint16 address) {
        return 0;
    }

    virtual void setHDMA(uint16 address, uint8 value) {};

    virtual bool set_8(uint16 address, uint8 value) {
        return false;
    }

    virtual void flag_interrupt(uint8 bit) {};
};

#endif //MY_APPLICATION_MEMORYHOOK_H
