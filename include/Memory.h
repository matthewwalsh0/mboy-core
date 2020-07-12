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

class Memory {
public:
    CoreMemory* coreMemory;
    Rom* rom;
    MemoryHook* cpu;
    MemoryHook* gpu;
    MemoryHook* timer;
    MemoryHook* apu;
    uint8 column = 0;

    void init(CoreMemory* coreMemory, Rom* rom, MemoryHook* cpu, MemoryHook* gpu, MemoryHook* timer, MemoryHook* apu);
    uint8 get_8(uint16 address);
    void set_8(uint16 address, uint8 value);
    void set_16(uint16 address, uint16 value);
    void flag_interrupt(uint8 bit);
    void dma(uint8 value);
};

#endif //MY_APPLICATION_MEMORY_H
