//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_GPU_H
#define MY_APPLICATION_GPU_H

#include "Types.h"
#include "Memory.h"
#include "Control.h"
#include "Pixels.h"
#include "Display.h"
#include "GUI.h"
#include "LogFile.h"
#include <chrono>

const uint8 SCREEN_HEIGHT = 144;
const uint8 SCREEN_WIDTH = 160;

class GPU : MemoryHook {
private:
    uint8 mode;
    uint16 cycleCount;
    uint16 line;
    Pixels pixels;
    Display display;
    Memory* memory;
    Control* control;
    bool coincidenceInterrupt;
    bool oamInterrupt;
    bool vblankInterrupt;
    bool hblankInterrupt;
    uint16 coincidenceLine;
    GUI* gui;
    LogFile logFile;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    uint16 frameCount = 0;
    
public:
    GPU(Memory* memory, GUI* gui);
    void step(uint16 lastInstructionDuration, Memory* memory, bool isColour, uint32 count);
    uint8 getStat();
    void setStat(uint8 value);
    void setControl(uint8 value);

private:
    uint8 get_8(uint16 address) override;
    bool set_8(uint16 address, uint8 value) override;
};


#endif //MY_APPLICATION_GPU_H