//
// Created by matthew on 12/07/2020.
//

#include "NearestNeighbourDownsampler.h"

const uint16 SAMPLE_COUNT = 4194304 / SAMPLE_RATE;

void NearestNeighbourDownsampler::addSample(uint16 volume, uint16 count, uint16 totalCount,
                                            uint16 maxVolume) {
    cycleCount += count;

    if(cycleCount >= SAMPLE_COUNT) {
        uint16 test = volume;
        float floatSample = (float) test / maxVolume;
        buffer[bufferCount] = floatSample;
        bufferCount += 1;
        cycleCount = cycleCount - SAMPLE_COUNT;
        negative = !negative;
    }
}

uint16 NearestNeighbourDownsampler::getSampleCount() {
    return bufferCount;
}

float *NearestNeighbourDownsampler::getSamples() {
    bufferCount = 0;
    return buffer;
}
