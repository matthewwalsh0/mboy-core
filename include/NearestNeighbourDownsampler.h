//
// Created by matthew on 12/07/2020.
//

#ifndef MBOY_ANDROID_NEARESTNEIGHBOURDOWNSAMPLER_H
#define MBOY_ANDROID_NEARESTNEIGHBOURDOWNSAMPLER_H


#include "APU.h"

class NearestNeighbourDownsampler : Downsampler {
    virtual void addSample(u_int16_t volume, u_int16_t count, u_int16_t totalCount, u_int16_t maxVolume);

    virtual u_int16_t getSampleCount();

    virtual float *getSamples();

private:
    float buffer[SAMPLE_PLAY_COUNT];
    u_int16_t bufferCount = 0;
    u_int16_t cycleCount = 0;
    bool negative = false;
};


#endif //MBOY_ANDROID_NEARESTNEIGHBOURDOWNSAMPLER_H
