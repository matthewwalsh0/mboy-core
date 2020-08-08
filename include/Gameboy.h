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
    Rom rom;
    Memory memory;
    CPU cpu;
    GPU gpu;
    APU apu;
    CoreMemory coreMemory;
    Timer timer;
    Joypad joypad;
    GUI* gui;
    config* config;
public:
    Gameboy(std::string path, GUI* gui, struct config* config);
    void run();
};


#endif //MY_APPLICATION_GAMEBOY_H
