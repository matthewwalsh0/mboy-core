#include "Memory.h"
#include "Bytes.h"
#include "MemoryMap.h"
#include <iostream>

const u_int16_t ADDRESS_DMA_TRANSFER = 0xFF46;
const u_int16_t ADDRESS_SPRITE_INFO_START = 0xFE00;

class DmaHook : public MemoryHook {
private:
    Memory* memory;
public:
    DmaHook(Memory* memory) {
        this->memory = memory;
    }

    bool set_8(u_int16_t address, u_int8_t value) {
        memory->dma(value);
        return true;
    }
};

class EHook : public MemoryHook {
    u_int8_t get_8(u_int16_t address) {
        return 0;
    }
};

Memory::Memory() {
    getters = new MemoryHook*[0xFFFF];
    setters = new MemoryHook*[0xFFFF];
    setters2 = new MemoryHook*[0xFFFF];

    core.set_8(0xFF10, 0x80);
    core.set_8(0xFF11, 0xBF);
    core.set_8(0xFF12, 0xF3);
    core.set_8(0xFF14, 0xBF);
    core.set_8(0xFF16, 0x3F);
    core.set_8(0xFF19, 0xBF);
    core.set_8(0xFF1A, 0x7F);
    core.set_8(0xFF1B, 0xFF);
    core.set_8(0xFF1C, 0x9F);
    core.set_8(0xFF1E, 0xBF);
    core.set_8(0xFF20, 0xFF);
    core.set_8(0xFF23, 0xBF);
    core.set_8(0xFF24, 0x77);
    core.set_8(0xFF25, 0xF3);
    core.set_8(0xFF26, 0xF1);
    core.set_8(0xFF47, 0xFC);
    core.set_8(0xFF48, 0xFF);
    core.set_8(0xFF48, 0xFF);

    registerGetter(0, 0xFFFF, (MemoryHook*) &core);
    registerGetter(0xE000, 0xEFFF, (MemoryHook*) new EHook());

    registerSetter(0, 0xFFFF, (MemoryHook*) &core);
    registerSetter(ADDRESS_DMA_TRANSFER, (MemoryHook*) new DmaHook(this));

    vram = new VRAM((MemoryRegister*) this);
    wram = new WRAM((MemoryRegister*) this);
}

void Memory::registerGetter(u_int16_t address, MemoryHook* getter) {
    getters[address] = getter;
}

void Memory::registerGetter(u_int16_t start, u_int16_t end, MemoryHook* getter) {
    for(u_int32_t i = start; i <= end; i++) {
        registerGetter(i, getter);
    }
}

void Memory::registerSetter(u_int16_t address, MemoryHook* setter, bool override) {
    if(override) {
        setters[address] = setter;
    } else {
        setters2[address] = setter;
    }
}

void Memory::registerSetter(u_int16_t start, u_int16_t end, MemoryHook* setter, bool override) {
    for(u_int32_t i = start; i <= end; i++) {
        registerSetter(i, setter, override);
    }
}

u_int8_t Memory::get_8(u_int16_t address) {
    MemoryHook* getter = getters[address];
    return getter->get_8(address);
}

u_int8_t Memory::get_8(u_int16_t address, u_int8_t bank) {
    MemoryHook* getter = getters[address];
    return getter->get_8(address, bank);
}

bool Memory::set_8(u_int16_t address, u_int8_t value) {
    MemoryHook* setter = setters[address];
    bool set = setter->set_8(address, value);

    if(!set) {
        core.set_8(address, value);
    }

    MemoryHook* setter2 = setters2[address];

    if(setter2 != nullptr) {
        setter2->set_8(address, value);
    }

    return true;
}

bool Memory::set_16(u_int16_t address, u_int16_t value) {
    set_8(address,  Bytes::split_16_lower(value));
    set_8(address + 1, Bytes::split_16_upper(value));
    return true;
}

void Memory::flagInterrupt(u_int8_t bit) {
    MemoryHook* flagger = setters[0];
    flagger->flagInterrupt(bit);
}

void Memory::dma(u_int8_t value) {
    u_int16_t start = Bytes::join_8(value, 0x00);
    u_int16_t end = Bytes::join_8(value, 0x9F) + 1;

    for(u_int16_t sourceAddress = start; sourceAddress < end; sourceAddress++) {
        u_int16_t relative = sourceAddress - start;
        u_int16_t targetAddress = ADDRESS_SPRITE_INFO_START + relative;
        u_int8_t sourceValue = get_8(sourceAddress);
        set_8(targetAddress, sourceValue);
    }
}
