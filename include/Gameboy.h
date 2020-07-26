//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_GAMEBOY_H
#define MY_APPLICATION_GAMEBOY_H


#include "Memory.h"
#include "CPU.h"
#include "Timer.h"
#include "GPU.h"
#include "GUI.h"
#include "APU.h"
#include "Joypad.h"
#include "Config.h"

class Gameboy {
private:
    Memory memory;
    CPU cpu;
    GPU gpu;
    APU apu;
    CoreMemory coreMemory;
    Rom* rom;
    Timer timer;
    Joypad joypad;
    GUI* gui;
    config* config;
public:
    Gameboy(Rom rom, GUI* gui, struct config* config);
    void run();
};


#endif //MY_APPLICATION_GAMEBOY_H
