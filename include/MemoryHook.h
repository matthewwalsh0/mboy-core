//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_MEMORYHOOK_H
#define MY_APPLICATION_MEMORYHOOK_H

#include <sys/types.h>

class MemoryHook {
public:
    virtual u_int8_t get_8(u_int16_t address) {
        return 0;
    }

    virtual u_int8_t get_8(u_int16_t address, u_int8_t bank) {
        return 0;
    }

    virtual u_int8_t get_core_8(u_int16_t address) {
        return 0;
    }

    virtual bool set_8(u_int16_t address, u_int8_t value) {
        return false;
    }

    virtual bool set_16(u_int16_t address, u_int16_t value) {
        return false;
    };

    virtual void flagInterrupt(u_int8_t bit) {};
};

#endif //MY_APPLICATION_MEMORYHOOK_H
