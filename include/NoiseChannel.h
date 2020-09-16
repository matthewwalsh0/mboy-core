//
// Created by matthew on 22/08/2020.
//

#ifndef MBOY_ANDROID_NOISECHANNEL_H
#define MBOY_ANDROID_NOISECHANNEL_H

#include "Types.h"

class NoiseChannel {
private:
    bool enabled;
    u_int16_t lsfr = 0xFF;
    u_int8_t divisor = 0;
    u_int8_t widthMode = 0;
    u_int8_t shift = 0;
    int32_t frequencyTimer = 0;
    bool trigger = false;
    u_int8_t volume = 0;
    u_int8_t lengthLoad = 0;
    bool lengthEnabled = false;
    u_int8_t lengthCounter = 0;
    bool envelopeEnabled = false;
    u_int8_t envelopePeriod = 0;
    bool envelopeAddMode = true;
    u_int8_t envelopeTimer = 0;
public:
    u_int16_t sample = 0;

    void step(u_int16_t lastInstructionDuration);
    void lengthStep();
    void volumeStep();
    u_int8_t get_8(u_int16_t address);
    bool set_8(u_int16_t address, u_int8_t value);
};


#endif //MBOY_ANDROID_NOISECHANNEL_H
