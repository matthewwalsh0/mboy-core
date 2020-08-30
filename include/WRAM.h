//
// Created by matthew on 29/07/2020.
//

#ifndef MBOY_ANDROID_WRAM_H
#define MBOY_ANDROID_WRAM_H


#include <sys/types.h>

class WRAM {
private:
    u_int8_t data[8][4 * 1024];
    u_int8_t bank = 1;
public:
    u_int8_t getBank();
    void setBank(u_int8_t value);
    u_int8_t get_8(u_int16_t address);
    void set_8(u_int16_t address, u_int8_t value);
};


#endif //MBOY_ANDROID_WRAM_H
