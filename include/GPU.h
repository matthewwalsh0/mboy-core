//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_GPU_H
#define MY_APPLICATION_GPU_H

#include <sys/types.h>
#include "Control.h"
#include "Pixels.h"
#include "Display.h"
#include "GUI.h"
#include "LogFile.h"
#include "Config.h"
#include "Memory.h"
#include <chrono>

const u_int8_t SCREEN_HEIGHT = 144;
const u_int8_t SCREEN_WIDTH = 160;

class GPU {
private:
    u_int8_t mode;
    u_int16_t cycleCount;
    
    Pixels pixels;
    MemoryHook* memory;
    Control* control;
    bool coincidenceInterrupt;
    bool oamInterrupt;
    bool vblankInterrupt;
    bool hblankInterrupt;
    
    GUI* gui;
    LogFile logFile;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    u_int16_t frameCount = 0;
    u_int16_t hdmaTarget = 0;
    u_int16_t hdmaSource = 0;
    struct config* config;
    
public:
u_int16_t line;
u_int16_t coincidenceLine;

    Display display;

    GPU(Memory* memory, GUI* gui, struct config* config);
    void step(u_int16_t lastInstructionDuration, MemoryHook* memory, bool isColour, u_int32_t count);
    u_int8_t getStat();
    void setStat(u_int8_t value);
    void setControl(u_int8_t value);
    u_int8_t getHDMA(u_int16_t address);
    void setHDMA(u_int16_t address, u_int8_t value);
};


#endif //MY_APPLICATION_GPU_H
