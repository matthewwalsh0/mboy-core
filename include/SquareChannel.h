//
// Created by matthew on 11/07/2020.
//

#ifndef MBOY_ANDROID_SQUARECHANNEL_H
#define MBOY_ANDROID_SQUARECHANNEL_H

#include "Types.h"
#include "../include/Types.h"
#include "../include/MemoryHook.h"

class SquareChannel : MemoryHook {
private:
    uint16 addressStart = 0;
    bool firstEnabled = false;
    bool enabled = false;
    uint16 frequency = 0;
    uint16 frequencyTimer = 0;
    uint16 duty = 0;
    uint16 dutyIndex = 0;
    bool trigger = false;
    bool dacEnabled = false;
    uint16 lengthLoad = 0;
    bool lengthEnabled = false;
    uint16 lengthCounter = 0;
    uint16 volume = 0;
public:
    uint16 sample = 0;

    SquareChannel(uint16 addressStart);
    void step(uint16 lastInstructionDuration);
    void lengthStep();
    uint8 get_8(uint16 address) override;
    bool set_8(uint16 address, uint8 value) override;
};


#endif //MBOY_ANDROID_SQUARECHANNEL_H
