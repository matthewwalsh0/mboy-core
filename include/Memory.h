//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_MEMORY_H
#define MY_APPLICATION_MEMORY_H

#include "Types.h"
#include "CoreMemory.h"
#include "Rom.h"
#include "MemoryHook.h"
#include "VRAM.h"
#include "Joypad.h"
#include "VRAM.h"
#include "WRAM.h"
#include "CPU.h"
#include "GPU.h"
#include "Timer.h"
#include "APU.h"

class Memory : MemoryHook {
public:
    CoreMemory* coreMemory;
    Rom* rom;
    CPU* cpu;
    GPU* gpu;
    Timer* timer;
    APU* apu;
    Joypad* joypad;
    VRAM vram;
    WRAM wram;

    void init(CoreMemory* coreMemory, Rom* rom, CPU* cpu, GPU* gpu,
            Timer* timer, APU* apu, Joypad* joypad);
    void dma(uint8 value);

    uint8 get_8(uint16 address) override;
    uint8 get_8(uint16 address, uint8 bank) override;
    bool set_8(uint16 address, uint8 value) override;
    bool set_16(uint16 address, uint16 value) override;
    void flagInterrupt(uint8 bit) override;
};
#endif //MY_APPLICATION_MEMORY_H
