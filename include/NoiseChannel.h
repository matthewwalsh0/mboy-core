//
// Created by matthew on 22/08/2020.
//

#ifndef MBOY_ANDROID_NOISECHANNEL_H
#define MBOY_ANDROID_NOISECHANNEL_H

#include "Types.h"

class NoiseChannel {
private:
    bool enabled;
    uint16 lsfr = 0xFF;
    uint8 divisor = 0;
    uint8 widthMode = 0;
    uint8 shift = 0;
    int32 frequencyTimer = 0;
    bool trigger = false;
    uint8 volume = 0;
    uint8 lengthLoad = 0;
    bool lengthEnabled = false;
    uint8 lengthCounter = 0;
    bool envelopeEnabled = false;
    uint8 envelopePeriod = 0;
    bool envelopeAddMode = true;
    uint8 envelopeTimer = 0;
public:
    uint16 sample = 0;

    void step(uint16 lastInstructionDuration);
    void lengthStep();
    void volumeStep();
    uint8 get_8(uint16 address);
    bool set_8(uint16 address, uint8 value);
};


#endif //MBOY_ANDROID_NOISECHANNEL_H
