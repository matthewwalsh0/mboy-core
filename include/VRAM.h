#ifndef MY_APPLICATION_VRAM_H
#define MY_APPLICATION_VRAM_H

#include <sys/types.h>

#include "MemoryRegister.h"

const u_int8_t VRAM_BANK_COUNT = 2;
const u_int16_t VRAM_BANK_SIZE = 8 * 1024;

class VRAM {
private:
    u_int8_t data[VRAM_BANK_COUNT * VRAM_BANK_SIZE];
public:
    u_int8_t bank;

    VRAM(MemoryRegister* memory);
};

#endif //MY_APPLICATION_VRAM_H
