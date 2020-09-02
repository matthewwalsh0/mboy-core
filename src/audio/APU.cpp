#include <stdexcept>
#include "APU.h"
#include "NearestNeighbourDownsampler.h"
#include <sys/types.h>
#include "GUI.h"
#include "WaveChannel.h"
#include "Bytes.h"

const u_int16_t CHANNEL_VOLUME = 15;

APU::APU(GUI* gui, Memory* memory, struct config* config) :
    square_1(SQUARE_1_ADDRESS_START),
    square_2(SQUARE_2_ADDRESS_START),
    wave((MemoryHook*) memory, WAVE_TABLE_START) {
    this->gui = gui;
    this->downsampler = (Downsampler*) new NearestNeighbourDownsampler();
    this->config = config;

    memory->registerSetter(SQUARE_1_ADDRESS_START, SQUARE_1_ADDRESS_START + 3, (MemoryHook*) this);
    memory->registerSetter(SQUARE_2_ADDRESS_START, SQUARE_2_ADDRESS_START + 3, (MemoryHook*) this);
    memory->registerSetter(WAVE_START, WAVE_START + 4, (MemoryHook*) this);
    memory->registerSetter(0xFF20, 0xFF23, (MemoryHook*) this);
    memory->registerSetter(0xFF26, (MemoryHook*) this);
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

u_int8_t APU::get_8(u_int16_t address) {
    throw std::invalid_argument("Invalid read from APU.");
}

bool APU::set_8(u_int16_t address, u_int8_t value) {
    if(address >= SQUARE_1_ADDRESS_START && address < SQUARE_1_ADDRESS_START + 4) {
        square_1.set_8(address, value);
        return false;
    }

    if(address >= SQUARE_2_ADDRESS_START && address < SQUARE_2_ADDRESS_START + 4) {
        square_2.set_8(address, value);
        return false;
    }

    if(address >= WAVE_START && address < WAVE_START + 5) {
        wave.set_8(address, value);
        return false;
    }

    if(address >= 0xFF20 && address <= 0xFF23) {
        noise.set_8(address, value);
        return false;
    }

    if(address == 0xFF26) {
        power = Bytes::getBit_8(value, 7);
        return true;
    }

    throw std::invalid_argument("Invalid write to APU.");
}
