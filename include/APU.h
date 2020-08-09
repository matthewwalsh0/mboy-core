//
// Created by matthew on 12/07/2020.
//

#ifndef MBOY_ANDROID_APU_H
#define MBOY_ANDROID_APU_H

#include "GUI.h"
#include "SquareChannel.h"
#include "WaveChannel.h"
#include "MemoryMap.h"
#include "Types.h"
#include "MemoryHook.h"

const uint16 SAMPLE_PLAY_COUNT = 1024;
const uint32 SAMPLE_RATE = 65536;

class Downsampler {
public:
    virtual void addSample(uint16 volume, uint16 count, uint16 totalCount, uint16 maxVolume) {};
    virtual uint16 getSampleCount() { return 0; }
    virtual float* getSamples() { return nullptr; }
};

class APU {
private:
    GUI *gui;
    Downsampler *downsampler;
    SquareChannel square_1;
    SquareChannel square_2;
    WaveChannel wave;
    uint16 frameSequencerCycleCount = 0;
    uint32 volumeEnvelopeCounter = 0;
    bool ready = false;
    bool power = false;
public:
    APU(GUI* gui, MemoryHook* memory);
    void step(uint16 lastInstructionDuration, uint32 count);
    uint8 get_8(uint16 address);
    bool set_8(uint16 address, uint8 value);
};


#endif //MBOY_ANDROID_APU_H
