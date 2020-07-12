//
// Created by matthew on 12/07/2020.
//

#ifndef MBOY_ANDROID_NEARESTNEIGHBOURDOWNSAMPLER_H
#define MBOY_ANDROID_NEARESTNEIGHBOURDOWNSAMPLER_H


#include "APU.h"

class NearestNeighbourDownsampler : Downsampler {
    virtual void addSample(uint16 volume, uint16 count, uint16 totalCount, uint16 maxVolume);

    virtual uint16 getSampleCount();

    virtual float *getSamples();

private:
    float buffer[SAMPLE_PLAY_COUNT];
    uint16 bufferCount = 0;
    uint16 cycleCount = 0;
    bool negative = false;
};


#endif //MBOY_ANDROID_NEARESTNEIGHBOURDOWNSAMPLER_H
