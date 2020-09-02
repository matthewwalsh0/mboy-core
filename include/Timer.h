#ifndef MY_APPLICATION_TIMER_H
#define MY_APPLICATION_TIMER_H

#include <sys/types.h>
#include "MemoryHook.h"
#include "Memory.h"

class Timer : MemoryHook {
private:
    u_int16_t divider = 0;
    u_int16_t counter = 0;
    u_int16_t modulo = 0;
    u_int16_t speed = 256;
    bool running = false;
    u_int16_t dividerCycleCount = 0;
    u_int16_t counterCycleCount = 0;
public:
    Timer(Memory* memory);
    void step(u_int16_t cycleCount, MemoryHook* memory);
    u_int8_t get_8(u_int16_t address) override;
    bool set_8(u_int16_t address, u_int8_t value) override;
};

#endif
