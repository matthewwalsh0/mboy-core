//
// Created by matthew on 12/07/2020.
//

#ifndef MBOY_ANDROID_APU_H
#define MBOY_ANDROID_APU_H

#include "GUI.h"
#include "SquareChannel.h"
#include "WaveChannel.h"
#include "NoiseChannel.h"
#include "MemoryMap.h"
#include <sys/types.h>
#include "MemoryHook.h"
#include "Config.h"

const u_int16_t SAMPLE_PLAY_COUNT = 1024;
const u_int32_t SAMPLE_RATE = 65536;

class Downsampler {
public:
    virtual void addSample(u_int16_t volume, u_int16_t count, u_int16_t totalCount, u_int16_t maxVolume) {};
    virtual u_int16_t getSampleCount() { return 0; }
    virtual float* getSamples() { return nullptr; }
};

class APU {
private:
    GUI *gui;
    Downsampler *downsampler;
    SquareChannel square_1;
    SquareChannel square_2;
    WaveChannel wave;
    NoiseChannel noise;
    u_int16_t frameSequencerCycleCount = 0;
    u_int32_t volumeEnvelopeCounter = 0;
    bool ready = false;
    bool power = false;
    struct config* config;
public:
    APU(GUI* gui, MemoryHook* memory, struct config* config);
    void step(u_int16_t lastInstructionDuration, u_int32_t count);
    u_int8_t get_8(u_int16_t address);
    bool set_8(u_int16_t address, u_int8_t value);
};


#endif //MBOY_ANDROID_APU_H
