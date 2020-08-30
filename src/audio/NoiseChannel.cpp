//
// Created by matthew on 22/08/2020.
//

#include <iostream>
#include <stdexcept>
#include "Bytes.h"
#include "MemoryMap.h"
#include "NoiseChannel.h"

const u_int8_t DIVISORS[] = {8, 16, 32, 48, 64, 80, 96, 112};

void NoiseChannel::step(u_int16_t lastInstructionDuration) {
    for(u_int16_t cycle = 0; cycle < lastInstructionDuration; cycle++) {
        frequencyTimer -= 1;

        if(trigger) {
            enabled = true;
            envelopeEnabled = true;
            envelopeTimer = envelopePeriod;
            frequencyTimer = DIVISORS[divisor] << shift;
            trigger = false;
            lsfr = 1 & 0b111111111111111;
            lengthCounter = lengthLoad;
        }

        if(frequencyTimer == 0) {
            frequencyTimer = DIVISORS[divisor] << shift;
            u_int16_t xorValue = (lsfr & 0x1) ^ ((lsfr >> 1) & 0x1);
            u_int16_t newLsfr = lsfr >> 1;
            newLsfr = xorValue > 0 ? Bytes::setBit_8(newLsfr, 15) : Bytes::setBit_8(newLsfr, 15);

            if(widthMode == 1) {
                newLsfr = xorValue > 0 ? Bytes::setBit_8(newLsfr, 6) : Bytes::clearBit_8(newLsfr, 6);
                newLsfr = newLsfr & 0x7F;
            }

            lsfr = newLsfr;
            sample = enabled && ((newLsfr & 0x1) == 0) ? volume : 0;
        }
    }
}

void NoiseChannel::lengthStep() {
    if(lengthEnabled && lengthCounter > 0) {
        lengthCounter -= 1;
        if(lengthCounter == 0) {
            enabled = false;
        }
    }
}

void NoiseChannel::volumeStep() {
    if(envelopeTimer > 0) {
        envelopeTimer -= 1;
    }

    if(envelopeTimer == 0) {
        envelopeTimer = envelopePeriod;

        if(envelopeEnabled && envelopePeriod != 0) {
            if (envelopeAddMode) {
                if(volume < 15) {
                    volume += 1;
                } else {
                    envelopeEnabled = false;
                }
            }

            if(!envelopeAddMode) {
                if(volume > 0) {
                    volume -= 1;
                } else {
                    envelopeEnabled = false;
                }
            }
        }
    }
}

u_int8_t NoiseChannel::get_8(u_int16_t address) {
    throw std::invalid_argument("Bad read from noise channel.");
}

bool NoiseChannel::set_8(u_int16_t address, u_int8_t value) {
    u_int16_t relativeAddress = address - 0xFF20;

    switch(relativeAddress) {
        case 0:
            lengthLoad = value & 0x3F;
            lengthCounter = 64 - lengthLoad;
            break;
        case 1:
            volume = value >> 4;
            envelopeAddMode = Bytes::getBit_8(value, 3);
            envelopePeriod = value & 0x7;
            break;
        case 2:
            shift = value >> 4;
            widthMode = (value >> 3) & 0x1;
            divisor = value & 0x7;
            break;
        case 3:
            trigger = Bytes::getBit_8(value, 7);
            lengthEnabled = Bytes::getBit_8(value, 6);
            break;
    }

    return true;
}
