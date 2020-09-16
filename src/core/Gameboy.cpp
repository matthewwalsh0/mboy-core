//
// Created by matthew on 05/07/2020.
//

#include "Gameboy.h"

Gameboy::Gameboy(std::string path, GUI* gui, Config* config) :
    memory(),
    rom(path, &memory),
    cpu(&memory),
    gpu(&memory, gui, config),
    apu(gui, &memory, config),
    timer(&memory),
    joypad(gui, &memory) {

    this->gui = gui;
    this->config = config;

    memory.set_8(LCD_CONTROL, 0x91);
    memory.set_8(ADDRESS_JOYPAD, 0x0F);
}

void Gameboy::run() {
    u_int32_t count = 0;
    bool isColour = rom.isColour;

    while(this->gui->isOpen()) {
        u_int16_t instructionDuration = cpu.step((MemoryHook*) &memory, count, false);
        gpu.step(instructionDuration, (MemoryHook*) &memory, isColour, count);

        if(!config->turbo) {
            apu.step(instructionDuration, count);
        }

        u_int8_t timerInstructionDuration = cpu.currentSpeed == 2 ?
            instructionDuration * 4 :
            instructionDuration;

        timer.step(timerInstructionDuration, (MemoryHook*) &memory);

        count += 1;
    }
}
