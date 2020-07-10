//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_COREMEMORY_H
#define MY_APPLICATION_COREMEMORY_H

#include "Types.h"

class CoreMemory {
private:
    uint8 data[64 * 1024] = {0};
public:
    CoreMemory();
    uint8 get_8(uint16 address);
    void set_8(uint16 address, uint8 value);
};


#endif //MY_APPLICATION_COREMEMORY_H
