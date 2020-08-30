//
// Created by matthew on 06/07/2020.
//

#ifndef MY_APPLICATION_VRAM_H
#define MY_APPLICATION_VRAM_H

#include <sys/types.h>

class VRAM {
private:
    u_int8_t data[2][8 * 1024];
public:
    u_int8_t bank;

    void setBank(u_int8_t value);
    u_int8_t get_8(u_int16_t address);
    u_int8_t get_8(u_int16_t address, u_int8_t bank);
    void set_8(u_int16_t address, u_int8_t value);
};


#endif //MY_APPLICATION_VRAM_H
