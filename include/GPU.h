//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_GPU_H
#define MY_APPLICATION_GPU_H

#include "Types.h"
#include "Control.h"
#include "Pixels.h"
#include "Display.h"
#include "GUI.h"
#include "LogFile.h"
#include "Config.h"
#include <chrono>

const uint8 SCREEN_HEIGHT = 144;
const uint8 SCREEN_WIDTH = 160;

class GPU {
private:
    uint8 mode;
    uint16 cycleCount;
    uint16 line;
    Pixels pixels;
    MemoryHook* memory;
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
    uint16 hdmaTarget = 0;
    uint16 hdmaSource = 0;
    struct config* config;
    
public:
    Display display;

    GPU(MemoryHook* memory, GUI* gui, struct config* config);
    void step(uint16 lastInstructionDuration, MemoryHook* memory, bool isColour, uint32 count);
    uint8 getStat();
    void setStat(uint8 value);
    void setControl(uint8 value);
    uint8 getHDMA(uint16 address);
    void setHDMA(uint16 address, uint8 value);
    uint8 get_8(uint16 address);
    bool set_8(uint16 address, uint8 value);
};


#endif //MY_APPLICATION_GPU_H
