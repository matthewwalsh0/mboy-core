//
// Created by matthew on 11/07/2020.
//

#ifndef MBOY_ANDROID_WAVECHANNEL_H
#define MBOY_ANDROID_WAVECHANNEL_H

#include "Types.h"
#include <Memory.h>

class WaveChannel {
private:
    Memory* memory;
    uint16 waveTableStart = 0;
    uint16 frequency = 0;
    int32 frequencyTimer = 0;
    uint8 position = 0;
    uint8 volume = 0;
    bool enabled = false;
    bool trigger = false;
    bool dacEnabled = false;
public:
    uint16 sample = 0;

    WaveChannel(Memory* memory, uint16 addressStart);
    void step(uint16 lastInstructionDuration);
    uint8 get_8(uint16 address);
    bool set_8(uint16 address, uint8 value);
};


#endif //MBOY_ANDROID_WAVECHANNEL_H
