//
// Created by matthew on 05/07/2020.
//

#include "Gameboy.h"

Gameboy::Gameboy(std::string path, GUI* gui, struct config* config) :
    rom(path),
    gpu((MemoryHook*) &memory, gui, config),
    apu(gui, (MemoryHook*) &memory),
    joypad(gui) {

    this->gui = gui;
    this->config = config;

    memory.init(&coreMemory, &rom, &cpu, &gpu, &timer, &apu, &joypad);
}

void Gameboy::run() {
    uint32 count = 0;
    bool isColour = rom.isColour;

    while(this->gui->isOpen()) {
        uint16 instructionDuration = cpu.step((MemoryHook*) &memory, count, false);
        gpu.step(instructionDuration, (MemoryHook*) &memory, isColour, count);

        if(!config->turbo) {
            apu.step(instructionDuration, count);
        }

        uint8 timerInstructionDuration = cpu.currentSpeed == 2 ?
            instructionDuration * 4 :
            instructionDuration;

        timer.step(timerInstructionDuration, (MemoryHook*) &memory);

        count += 1;
    }
}
