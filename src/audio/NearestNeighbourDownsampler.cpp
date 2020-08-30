//
// Created by matthew on 12/07/2020.
//

#include "NearestNeighbourDownsampler.h"

const u_int16_t SAMPLE_COUNT = 4194304 / SAMPLE_RATE;

void NearestNeighbourDownsampler::addSample(u_int16_t volume, u_int16_t count, u_int16_t totalCount,
                                            u_int16_t maxVolume) {
    cycleCount += count;

    if(cycleCount >= SAMPLE_COUNT) {
        u_int16_t test = volume;
        float floatSample = (float) test / maxVolume;
        buffer[bufferCount] = floatSample;
        bufferCount += 1;
        cycleCount = cycleCount - SAMPLE_COUNT;
        negative = !negative;
    }
}

u_int16_t NearestNeighbourDownsampler::getSampleCount() {
    return bufferCount;
}

float *NearestNeighbourDownsampler::getSamples() {
    bufferCount = 0;
    return buffer;
}
