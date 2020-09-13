#ifndef MBOY_ANDROID_WRAM_H
#define MBOY_ANDROID_WRAM_H

#include <sys/types.h>

#include "MemoryHook.h"
#include "MemoryRegister.h"

const u_int8_t WRAM_BANK_COUNT = 8;
const u_int16_t WRAM_BANK_SIZE = 4 * 1024;

class WRAM {
private:
    u_int8_t data[WRAM_BANK_COUNT][WRAM_BANK_SIZE];
    u_int8_t bank = 1;
public:
    WRAM(MemoryRegister* memory);
    u_int8_t getBank();
    void setBank(u_int8_t value);
};

#endif //MBOY_ANDROID_WRAM_H
