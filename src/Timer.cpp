//
// Created by matthew on 05/07/2020.
//

#include "Timer.h"
#include "Bytes.h"
#include "MemoryMap.h"

const uint16 SPEEDS[] = {1024, 16, 64, 256};

void Timer::step(uint16 cycleCount, Memory *memory) {
    for(uint16 i = 0; i < cycleCount; i++) {
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
                    memory->flag_interrupt(INTERRUPT_BIT_TIMER);
                }
            }
        }
    }
}

uint8 Timer::get_8(uint16 address) {
    uint16 relativeAddress = address - ADDRESS_DIVIDER;
    uint8 control = 0;

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

bool Timer::set_8(uint16 address, uint8 value) {
    uint16 relativeAddress = address - ADDRESS_DIVIDER;

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
