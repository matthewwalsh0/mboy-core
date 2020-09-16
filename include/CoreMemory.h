#ifndef MY_APPLICATION_COREMEMORY_H
#define MY_APPLICATION_COREMEMORY_H

#include "Types.h"

class CoreMemory {
private:
    u_int8_t data[64 * 1024] = {0};
public:
    u_int8_t get_8(u_int16_t address);
    bool set_8(u_int16_t address, u_int8_t value);
};

#endif //MY_APPLICATION_COREMEMORY_H
