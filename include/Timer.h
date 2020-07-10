//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_TIMER_H
#define MY_APPLICATION_TIMER_H

#include "Types.h"
#include "MemoryHook.h"
#include "Memory.h"

class Timer : MemoryHook {
private:
    uint16 divider = 0;
    uint16 counter = 0;
    uint16 modulo = 0;
    uint16 speed = 256;
    bool running = false;
    uint16 dividerCycleCount = 0;
    uint16 counterCycleCount = 0;
public:
    void step(uint16 cycleCount, Memory* memory);
    uint8 get_8(uint16 address) override;
    bool set_8(uint16 address, uint8 value) override;
};


#endif //MY_APPLICATION_TIMER_H
