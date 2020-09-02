#include <stdexcept>
#include "Timer.h"
#include "Bytes.h"
#include "MemoryMap.h"
#include "Memory.h"

const u_int16_t SPEEDS[] = {1024, 16, 64, 256};

Timer::Timer(Memory* memory) {
    memory->registerGetter(ADDRESS_DIVIDER, ADDRESS_DIVIDER + 3, (MemoryHook*) this);
    memory->registerSetter(ADDRESS_DIVIDER, ADDRESS_DIVIDER + 3, (MemoryHook*) this);
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

u_int8_t Timer::get_8(u_int16_t address) {
    u_int16_t relativeAddress = address - ADDRESS_DIVIDER;
    u_int8_t control = 0;

    switch(relativeAddress) {
        case 0:
            return divider;
        case 1:
            return counter;
        case 2:
            return modulo;
        case 3:

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
        default:
            throw std::invalid_argument("Invalid address passed to Timer.get_8");
    }
}

bool Timer::set_8(u_int16_t address, u_int8_t value) {
    u_int16_t relativeAddress = address - ADDRESS_DIVIDER;

    switch(relativeAddress) {
        case 0:
            divider = 0;
            break;
        case 1:
            counter = value;
            break;
        case 3:
            speed = SPEEDS[value & 0x3];
            running = Bytes::getBit_8(value, 2);
            break;
    }

    return true;
}
