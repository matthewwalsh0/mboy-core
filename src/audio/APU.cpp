#include "APU.h"

#include <stdexcept>
#include <sys/types.h>

#include "NearestNeighbourDownsampler.h"
#include "GUI.h"
#include "WaveChannel.h"
#include "Bytes.h"
#include "MemoryRegister.h"

const u_int16_t CHANNEL_VOLUME = 15;

APU::APU(GUI* gui, Memory* memory, struct config* config) :
    square_1(SQUARE_1_ADDRESS_START),
    square_2(SQUARE_2_ADDRESS_START),
    wave((MemoryHook*) memory, WAVE_TABLE_START) {
    this->gui = gui;
    this->downsampler = (Downsampler*) new NearestNeighbourDownsampler();
    this->config = config;

    memory->registerSetter(SQUARE_1_ADDRESS_START, SQUARE_1_ADDRESS_START + 3, [this]MEMORY_SETTER_LAMBDA {
        square_1.set_8(address, value);
        return false;
    });

    memory->registerSetter(SQUARE_2_ADDRESS_START, SQUARE_2_ADDRESS_START + 3, [this]MEMORY_SETTER_LAMBDA {
        square_2.set_8(address, value);
        return false;
    });

    memory->registerSetter(WAVE_START, WAVE_START + 4, [this]MEMORY_SETTER_LAMBDA {
        wave.set_8(address, value);
        return false;
    });

    memory->registerSetter(ADDRESS_NOISE_START, ADDRESS_NOISE_START + 3, [this]MEMORY_SETTER_LAMBDA {
        noise.set_8(address, value);
        return false;
    });

    memory->registerSetter(ADDRESS_APU_POWER, [this]MEMORY_SETTER_LAMBDA {
        power = Bytes::getBit_8(value, 7);
        return true;
    });
}

void APU::step(u_int16_t lastInstructionDuration, u_int32_t count) {
    if(!power) return;

    square_1.step(lastInstructionDuration);
    square_2.step(lastInstructionDuration);
    wave.step(lastInstructionDuration);
    noise.step(lastInstructionDuration);

    frameSequencerCycleCount += lastInstructionDuration;
    volumeEnvelopeCounter += lastInstructionDuration;

    u_int16_t finalVolume = 0;
    u_int16_t maxVolume = 0;

    if(config->square1) {
        finalVolume += square_1.sample;
        maxVolume += CHANNEL_VOLUME;
    }

    if(config->square2) {
        finalVolume += square_2.sample;
        maxVolume += CHANNEL_VOLUME;
    }

    if(config->wave) {
        finalVolume += wave.sample;
        maxVolume += CHANNEL_VOLUME;
    }

    if(config->noise) {
        finalVolume += noise.sample;
        maxVolume += CHANNEL_VOLUME;
    }

    if(finalVolume > maxVolume) {
        finalVolume = maxVolume;
    }

    if(!ready) {
        ready = finalVolume > 0;
    }

    if(!ready) return;

    finalVolume = config->audio ? finalVolume : 0;

    downsampler->addSample(finalVolume, lastInstructionDuration, count, maxVolume);

    if(frameSequencerCycleCount >= 16384) {
        square_1.lengthStep();
        square_2.lengthStep();
        noise.lengthStep();
        frameSequencerCycleCount = 0;
    }

    if(volumeEnvelopeCounter >= 65536) {
        noise.volumeStep();
        volumeEnvelopeCounter = 0;
    }

    if(downsampler->getSampleCount() == SAMPLE_PLAY_COUNT) {
        float* samples = downsampler->getSamples();
        gui->playAudio(samples, SAMPLE_PLAY_COUNT);
    }
}
