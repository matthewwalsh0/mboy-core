//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_MEMORY_H
#define MY_APPLICATION_MEMORY_H

#include <sys/types.h>
#include "MemoryHook.h"
#include "MemoryRegister.h"
#include "CoreMemory.h"
#include "VRAM.h"
#include "WRAM.h"

class Memory : MemoryHook, MemoryRegister {
private:
    CoreMemory core;
    VRAM* vram;
    WRAM* wram;
    MemoryHook** getters;
    MemoryHook** setters;
    MemoryHook** setters2;
public:
    Memory();
    void registerGetter(u_int16_t address, MemoryHook* getter) override;
    void registerGetter(u_int16_t start, u_int16_t end, MemoryHook* getter) override;
    void registerSetter(u_int16_t address, MemoryHook* setter, bool override = true) override;
    void registerSetter(u_int16_t start, u_int16_t end, MemoryHook* setter, bool override = true) override;
    void dma(u_int8_t value);
    u_int8_t get_8(u_int16_t address) override;
    u_int8_t get_8(u_int16_t address, u_int8_t bank) override;
    bool set_8(u_int16_t address, u_int8_t value) override;
    bool set_16(u_int16_t address, u_int16_t value) override;
    void flagInterrupt(u_int8_t bit) override;
};
#endif //MY_APPLICATION_MEMORY_H
