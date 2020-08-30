//
// Created by matthew on 11/07/2020.
//

#ifndef MBOY_ANDROID_WAVECHANNEL_H
#define MBOY_ANDROID_WAVECHANNEL_H

#include <sys/types.h>
#include "MemoryHook.h"

class WaveChannel {
private:
    MemoryHook* memory;
    u_int16_t waveTableStart = 0;
    u_int16_t frequency = 0;
    int32_t frequencyTimer = 0;
    u_int8_t position = 0;
    u_int8_t volume = 0;
    bool enabled = false;
    bool trigger = false;
    bool dacEnabled = false;
public:
    u_int16_t sample = 0;

    WaveChannel(MemoryHook* memory, u_int16_t addressStart);
    void step(u_int16_t lastInstructionDuration);
    u_int8_t get_8(u_int16_t address);
    bool set_8(u_int16_t address, u_int8_t value);
};


#endif //MBOY_ANDROID_WAVECHANNEL_H
