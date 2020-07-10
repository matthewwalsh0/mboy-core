//
// Created by matthew on 05/07/2020.
//

#include "Gameboy.h"

Gameboy::Gameboy(Rom rom, GUI* gui) : gpu(&memory, gui) {
    this->rom = &rom;
    this->gui = gui;
    memory.init(&coreMemory, &rom, (MemoryHook*) &cpu, (MemoryHook*) &gpu, (MemoryHook*) &timer);
}

void Gameboy::run() {
    uint32 count = 0;
    bool isColour = rom->isColour;

    while(this->gui->isOpen()) {
        uint16 instructionDuration = cpu.step(&memory, count, false);
        gpu.step(instructionDuration, &memory, isColour, count);
        timer.step(instructionDuration, &memory);

        count += 1;
    }
}
