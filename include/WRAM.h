//
// Created by matthew on 29/07/2020.
//

#ifndef MBOY_ANDROID_WRAM_H
#define MBOY_ANDROID_WRAM_H


#include "Types.h"

class WRAM {
private:
    uint8 data[8][4 * 1024];
    uint8 bank = 1;
public:
    uint8 getBank();
    void setBank(uint8 value);
    uint8 get_8(uint16 address);
    void set_8(uint16 address, uint8 value);
};


#endif //MBOY_ANDROID_WRAM_H
