//
// Created by matthew on 11/07/2020.
//

#include <stdexcept>
#include "Bytes.h"
#include "SquareChannel.h"

const bool DUTY_CYCLE_0[] = {false, false, false, false, false, false, false, true};
const bool DUTY_CYCLE_1[] = {true, false, false, false, false, false, false, true};
const bool DUTY_CYCLE_2[] = {true, false, false, false, false, true, true, true};
const bool DUTY_CYCLE_3[] = {false, true, true, true, true, true, true, false};
const bool* DUTY_CYCLES[] = {DUTY_CYCLE_0, DUTY_CYCLE_1, DUTY_CYCLE_2, DUTY_CYCLE_3};

SquareChannel::SquareChannel(u_int16_t addressStart) {
    this->addressStart = addressStart;
}

void SquareChannel::step(u_int16_t lastInstructionDuration) {
    u_int8_t extraCycles = 0;

    sample = 0;

    if(trigger) {
        firstEnabled = true;
        enabled = true;
        frequencyTimer = (2048 - frequency) * 4;
        trigger = false;

        if(lengthCounter == 0) {
            lengthCounter = 64;
        }
    }

    if(!firstEnabled) return;

    if(frequencyTimer != 0) {
        if(frequencyTimer < lastInstructionDuration) {
            frequencyTimer = 0;
            extraCycles = lastInstructionDuration - frequencyTimer;
        } else {
            frequencyTimer -= lastInstructionDuration;
        }
    }

    if(frequencyTimer <= 0) {
        frequencyTimer = ((2048 - frequency) * 4) - extraCycles;
        dutyIndex += 1;

        if(dutyIndex == 8) {
            dutyIndex = 0;
        }
    }

    if(enabled && dacEnabled) {
        sample = DUTY_CYCLES[duty][dutyIndex] ? volume : 0;
    }
}

void SquareChannel::lengthStep() {
    if(lengthEnabled && lengthCounter > 0) {
        lengthCounter -= 1;

        if(lengthCounter == 0) {
            enabled = false;
        }
    }
}

u_int8_t SquareChannel::get_8(u_int16_t address) {
    throw std::invalid_argument("Bad read from square channel.");
}

bool SquareChannel::set_8(u_int16_t address, u_int8_t value) {
    int relativeAddress = address - addressStart;

    switch(relativeAddress) {
        case 0:
            duty = (value >> 6) & 0x3;
            lengthLoad = value & 0x3F;
            lengthCounter = 64 - lengthLoad;
            break;
        case 1:
            dacEnabled = (value & 0xF8) > 0;
            volume = value >> 4;
            break;
        case 2:
            frequency = (frequency & 0x700) | value;
            break;
        case 3:
            frequency = (frequency & 0xFF) | ((value & 0x7) << 8);
            trigger = Bytes::getBit_8(value, 7);
            lengthEnabled = Bytes::getBit_8(value, 6);
            break;
    }

    return true;
}
