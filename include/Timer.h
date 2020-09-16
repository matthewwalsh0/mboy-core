#ifndef MY_APPLICATION_TIMER_H
#define MY_APPLICATION_TIMER_H

#include "Types.h"

#include "Memory.h"

class Timer {
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
};

#endif
