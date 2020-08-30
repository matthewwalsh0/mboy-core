//
// Created by matthew on 11/07/2020.
//

#include <iostream>
#include <stdexcept>
#include "Bytes.h"
#include "MemoryMap.h"
#include <WaveChannel.h>

const u_int8_t WAVE_VOLUME_SHIFT[] = {4, 0, 1, 2};

WaveChannel::WaveChannel(MemoryHook* memory, u_int16_t addressStart) {
    this->memory = memory;
    this->waveTableStart = addressStart;
}

void WaveChannel::step(u_int16_t lastInstructionDuration) {
    u_int16_t extraCycles = 0;

    sample = 0;

    if(trigger) {
        enabled = true;
        frequencyTimer = (2048 - frequency) * 4;
        trigger = false;
    }

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
        position += 1;

        if(position == 32) {
            position = 0;
        }
    }

    if(enabled && dacEnabled) {
        u_int16_t byteIndex = position / 2;
        bool useUpper = position % 2 == 0;
        u_int8_t currentByte = memory->get_8(waveTableStart + byteIndex);
        u_int8_t upper = Bytes::split_8_upper(currentByte);
        u_int8_t lower = Bytes::split_8_lower(currentByte);
        u_int8_t originalSample = useUpper ? upper : lower;
        u_int8_t shift = WAVE_VOLUME_SHIFT[volume];
        u_int8_t finalSample = originalSample >> shift;

        sample = finalSample;
    }
}

u_int8_t WaveChannel::get_8(u_int16_t address) {
    throw std::invalid_argument("Bad read from wave channel.");
}

bool WaveChannel::set_8(u_int16_t address, u_int8_t value) {
    u_int8_t relativeAddress = address - WAVE_START;

    switch(relativeAddress) {
        case 0:
            dacEnabled = Bytes::getBit_8(value, 7);
            break;
        case 2:
            volume = (value >> 5) & 0x3;
            break;
        case 3:
            frequency = (frequency & 0x700) | value;
            break;
        case 4:
            trigger = Bytes::getBit_8(value, 7);
            frequency = (frequency & 0xFF) | ((value & 0x7) << 8);
            break;
    }

    return true;
}
