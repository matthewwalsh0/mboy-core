//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_MEMORY_H
#define MY_APPLICATION_MEMORY_H

#include <sys/types.h>
#include <functional>
#include <vector>

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
    std::vector<MEMORY_GETTER> getters;
    std::vector<std::vector<MEMORY_SETTER>> setters;
    MEMORY_FLAGGER flagger;
public:
    Memory();
    void dma(u_int8_t value);
    
    // MemoryRegister.h
    virtual void registerGetter(u_int16_t address, MEMORY_GETTER getter) override;
    virtual void registerGetter(u_int16_t start, u_int16_t end, MEMORY_GETTER getter) override;
    virtual void registerSetter(u_int16_t address, MEMORY_SETTER setter, bool override = true) override;
    virtual void registerSetter(u_int16_t start, u_int16_t end, MEMORY_SETTER setter, bool override = true) override;
    virtual void registerFlagger(MEMORY_FLAGGER flagger) override;
    
    // MemoryHook.h
    u_int8_t get_8(u_int16_t address) override;
    u_int8_t get_8(u_int16_t address, u_int8_t bank) override;
    bool set_8(u_int16_t address, u_int8_t value) override;
    bool set_16(u_int16_t address, u_int16_t value) override;
    void flagInterrupt(u_int8_t bit) override;
};
#endif //MY_APPLICATION_MEMORY_H
