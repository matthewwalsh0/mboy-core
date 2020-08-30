//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_MEMORY_H
#define MY_APPLICATION_MEMORY_H

#include <sys/types.h>
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
    void dma(u_int8_t value);

    u_int8_t get_8(u_int16_t address) override;
    u_int8_t get_8(u_int16_t address, u_int8_t bank) override;
    u_int8_t get_core_8(u_int16_t address) override;
    bool set_8(u_int16_t address, u_int8_t value) override;
    bool set_16(u_int16_t address, u_int16_t value) override;
    void flagInterrupt(u_int8_t bit) override;
};
#endif //MY_APPLICATION_MEMORY_H
