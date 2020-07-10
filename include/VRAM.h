//
// Created by matthew on 06/07/2020.
//

#ifndef MY_APPLICATION_VRAM_H
#define MY_APPLICATION_VRAM_H

#include "Types.h"

class VRAM {
private:
    uint8 data[2][8 * 1024];
public:
    uint8 bank;

    void setBank(uint8 value);
    uint8 get_8(uint16 address);
    uint8 get_8(uint16 address, uint8 bank);
    void set_8(uint16 address, uint8 value);
};


#endif //MY_APPLICATION_VRAM_H
