//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_COREMEMORY_H
#define MY_APPLICATION_COREMEMORY_H

#include <sys/types.h>
#include "MemoryHook.h"

class CoreMemory : public MemoryHook {
private:
    u_int8_t data[64 * 1024] = {0};
public:
    u_int8_t get_8(u_int16_t address);
    bool set_8(u_int16_t address, u_int8_t value);
};


#endif //MY_APPLICATION_COREMEMORY_H
