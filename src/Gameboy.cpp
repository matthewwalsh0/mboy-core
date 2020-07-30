//
// Created by matthew on 05/07/2020.
//

#include "Gameboy.h"

Gameboy::Gameboy(Rom rom, GUI* gui, struct config* config) : gpu(&memory, gui, config), apu(gui, &memory), joypad(gui) {
    this->rom = &rom;
    this->gui = gui;
    this->config = config;

    memory.init(&coreMemory, &rom, (MemoryHook*) &cpu, (MemoryHook*) &gpu,
            (MemoryHook*) &timer, (MemoryHook*) &apu, (MemoryHook*) &joypad);
}

void Gameboy::run() {
    uint32 count = 0;
    bool isColour = rom->isColour;

    while(this->gui->isOpen()) {
        uint16 instructionDuration = cpu.step(&memory, count, false);
        gpu.step(instructionDuration, &memory, isColour, count);

        if(!config->turbo) {
            apu.step(instructionDuration, count);
        }

        timer.step(instructionDuration, &memory);

        count += 1;
    }
}
