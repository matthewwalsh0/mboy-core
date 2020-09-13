#ifndef MBOY_ANDROID_SQUARECHANNEL_H
#define MBOY_ANDROID_SQUARECHANNEL_H

#include <sys/types.h>

class SquareChannel {
private:
    u_int16_t addressStart = 0;
    bool firstEnabled = false;
    bool enabled = false;
    u_int16_t frequency = 0;
    int32_t frequencyTimer = 0;
    u_int16_t duty = 0;
    u_int16_t dutyIndex = 0;
    bool trigger = false;
    bool dacEnabled = false;
    u_int16_t lengthLoad = 0;
    bool lengthEnabled = false;
    u_int16_t lengthCounter = 0;
    u_int16_t volume = 0;
public:
    u_int16_t sample = 0;

    SquareChannel(u_int16_t addressStart);
    void step(u_int16_t lastInstructionDuration);
    void lengthStep();
    u_int8_t get_8(u_int16_t address, u_int8_t bank);
    bool set_8(u_int16_t address, u_int8_t value);
};

#endif //MBOY_ANDROID_SQUARECHANNEL_H
