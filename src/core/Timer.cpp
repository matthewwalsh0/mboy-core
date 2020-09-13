#include "Timer.h"

#include <stdexcept>

#include "Bytes.h"
#include "MemoryMap.h"
#include "Memory.h"
#include "MemoryRegister.h"

const u_int16_t SPEEDS[] = {1024, 16, 64, 256};

Timer::Timer(Memory* memory) {
    memory->registerGetter(ADDRESS_DIVIDER, [this]MEMORY_GETTER_LAMBDA {
        return divider;
    });
    
    memory->registerGetter(ADDRESS_DIVIDER + 1, [this]MEMORY_GETTER_LAMBDA {
        return counter;
    });
    
    memory->registerGetter(ADDRESS_DIVIDER + 2, [this]MEMORY_GETTER_LAMBDA {
        return modulo;
    });
    
    memory->registerGetter(ADDRESS_DIVIDER + 3, [this]MEMORY_GETTER_LAMBDA {
        u_int8_t control = 0;
        if(speed == SPEEDS[1] || speed == SPEEDS[3]) {
           control = Bytes::setBit_8(control, 0);
        }
        if(speed == SPEEDS[2] || speed == SPEEDS[3]) {
           control = Bytes::setBit_8(control, 1);
        }
        if(running) {
           control = Bytes::setBit_8(control, 2);
        }
        return control;
    });
    
    memory->registerSetter(ADDRESS_DIVIDER, [this]MEMORY_SETTER_LAMBDA {
        divider = 0;
        return true;
    });

    memory->registerSetter(ADDRESS_DIVIDER + 1, [this]MEMORY_SETTER_LAMBDA {
        counter = value;
        return true;
    });

    memory->registerSetter(ADDRESS_DIVIDER + 2, []MEMORY_SETTER_LAMBDA {
        return true;
    });
    
    memory->registerSetter(ADDRESS_DIVIDER + 3, [this]MEMORY_SETTER_LAMBDA {
        speed = SPEEDS[value & 0x3];
        running = Bytes::getBit_8(value, 2);
        return true;
    });
}

void Timer::step(u_int16_t cycleCount, MemoryHook *memory) {
    for(u_int16_t i = 0; i < cycleCount; i++) {
        dividerCycleCount += 1;

        if(dividerCycleCount == 256) {
            divider = Bytes::wrappingAdd_8(divider, 1);
            dividerCycleCount = 0;
        }

        if(running) {
            counterCycleCount += 1;

            if(counterCycleCount == speed) {
                counter = Bytes::wrappingAdd_8(counter, 1);
                counterCycleCount = 0;

                if(counter == 0) {
                    counter = modulo;
                    memory->flagInterrupt(INTERRUPT_BIT_TIMER);
                }
            }
        }
    }
}
