//
// Created by matthew on 11/07/2020.
//

#include <iostream>
#include <stdexcept>
#include "Bytes.h"
#include "MemoryMap.h"
#include <WaveChannel.h>

const uint8 WAVE_VOLUME_SHIFT[] = {4, 0, 1, 2};

WaveChannel::WaveChannel(MemoryHook* memory, uint16 addressStart) {
    this->memory = memory;
    this->waveTableStart = addressStart;
}

void WaveChannel::step(uint16 lastInstructionDuration) {
    uint16 extraCycles = 0;

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
        uint16 byteIndex = position / 2;
        bool useUpper = position % 2 == 0;
        uint8 currentByte = memory->get_8(waveTableStart + byteIndex);
        uint8 upper = Bytes::split_8_upper(currentByte);
        uint8 lower = Bytes::split_8_lower(currentByte);
        uint8 originalSample = useUpper ? upper : lower;
        uint8 shift = WAVE_VOLUME_SHIFT[volume];
        uint8 finalSample = originalSample >> shift;

        sample = finalSample;
    }
}

uint8 WaveChannel::get_8(uint16 address) {
    throw std::invalid_argument("Bad read from wave channel.");
}

bool WaveChannel::set_8(uint16 address, uint8 value) {
    uint8 relativeAddress = address - WAVE_START;

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
