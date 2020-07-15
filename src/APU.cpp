//
// Created by matthew on 12/07/2020.
//

#include <stdexcept>
#include "APU.h"
#include "NearestNeighbourDownsampler.h"
#include "Types.h"
#include "GUI.h"
#include "WaveChannel.h"

const uint16 CHANNEL_VOLUME = 15;

APU::APU(GUI* gui, Memory* memory) :
    square_1(SQUARE_1_ADDRESS_START),
    square_2(SQUARE_2_ADDRESS_START),
    wave(memory, WAVE_TABLE_START) {
    this->gui = gui;
    this->downsampler = (Downsampler*) new NearestNeighbourDownsampler();
}

void APU::step(uint16 lastInstructionDuration, uint32 count) {
    //if(!m_power.On) return;

    square_1.step(lastInstructionDuration);
    square_2.step(lastInstructionDuration);
    wave.step(lastInstructionDuration);

    frameSequencerCycleCount += lastInstructionDuration;
    volumeEnvelopeCounter += lastInstructionDuration;

    uint16 finalVolume = 0;
    uint16 maxVolume = 0;

    finalVolume += square_1.sample;
    maxVolume += CHANNEL_VOLUME;

    finalVolume += square_2.sample;
    maxVolume += CHANNEL_VOLUME;

    finalVolume += wave.sample;
    maxVolume += CHANNEL_VOLUME;

    if(finalVolume > maxVolume) {
        finalVolume = maxVolume;
    }

    if(!ready) {
        ready = finalVolume > 0;
    }

    if(!ready) return;

    downsampler->addSample(finalVolume, lastInstructionDuration, count, maxVolume);

    if(frameSequencerCycleCount >= 16384) {
        square_1.lengthStep();
        square_2.lengthStep();
        frameSequencerCycleCount = 0;
    }

    if(volumeEnvelopeCounter >= 65536) {
        volumeEnvelopeCounter = 0;
    }

    if(downsampler->getSampleCount() == SAMPLE_PLAY_COUNT) {
        float* samples = downsampler->getSamples();
        gui->playAudio(samples, SAMPLE_PLAY_COUNT);
    }
}

uint8 APU::get_8(uint16 address) {
    throw std::invalid_argument("Invalid read from APU.");
}

bool APU::set_8(uint16 address, uint8 value) {
    if(address >= SQUARE_1_ADDRESS_START && address < SQUARE_1_ADDRESS_START + 4)
        return square_1.set_8(address, value);

    if(address >= SQUARE_2_ADDRESS_START && address < SQUARE_2_ADDRESS_START + 4)
        return square_2.set_8(address, value);

    if(address >= WAVE_START && address < WAVE_START + 5)
        return wave.set_8(address, value);

    throw std::invalid_argument("Invalid write to APU.");
}
