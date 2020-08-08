//
// Created by matthew on 05/07/2020.
//

#include "Gameboy.h"

Gameboy::Gameboy(std::string path, GUI* gui, struct config* config) : rom(path), gpu(&memory, gui, config), apu(gui, &memory), joypad(gui) {
    this->gui = gui;
    this->config = config;

    memory.init(&coreMemory, &rom, (MemoryHook*) &cpu, (MemoryHook*) &gpu,
            (MemoryHook*) &timer, (MemoryHook*) &apu, (MemoryHook*) &joypad);
}

void Gameboy::run() {
    uint32 count = 0;
    bool isColour = rom.isColour;

    while(this->gui->isOpen()) {
        uint16 instructionDuration = cpu.step(&memory, count, false);
        gpu.step(instructionDuration, &memory, isColour, count);

        if(!config->turbo) {
            apu.step(instructionDuration, count);
        }

        uint8 timerInstructionDuration = cpu.currentSpeed == 2 ?
            instructionDuration * 4 :
            instructionDuration;

        timer.step(timerInstructionDuration, &memory);

        count += 1;
    }
}
