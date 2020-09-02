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
#include "Rom.h"
#include "CoreMemory.h"

class Gameboy {
private:
    Memory memory;
    Rom rom;
    CPU cpu;
    GPU gpu;
    APU apu;
    Timer timer;
    Joypad joypad;
    GUI* gui;
    config* config;
public:
    Gameboy(std::string path, GUI* gui, struct config* config);
    void run();
};

#endif
