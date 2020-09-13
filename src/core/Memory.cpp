#include "Memory.h"

#include <iostream>

#include "Bytes.h"
#include "MemoryMap.h"

const u_int16_t ADDRESS_DMA_TRANSFER = 0xFF46;
const u_int16_t ADDRESS_SPRITE_INFO_START = 0xFE00;

Memory::Memory() {
    for(u_int32_t i = 0; i < 0xFFFF; i++) {
        getters.push_back(nullptr);
        std::vector<MEMORY_SETTER> vectorList;
        setters.push_back(vectorList);
    }

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

    registerGetter(0, 0xFFFF, [this]MEMORY_GETTER_LAMBDA {
        return core.get_8(address);
    });

    registerGetter(0xE000, 0xEFFF, []MEMORY_GETTER_LAMBDA {
        return 0;
    });

    registerSetter(0, 0xFFFF, [this]MEMORY_SETTER_LAMBDA {
        return core.set_8(address, value);
    });

    registerSetter(ADDRESS_DMA_TRANSFER, [this]MEMORY_SETTER_LAMBDA {
        dma(value);
        return true;
    });

    vram = new VRAM((MemoryRegister*) this);
    wram = new WRAM((MemoryRegister*) this);
}

void Memory::registerGetter(u_int16_t address, MEMORY_GETTER getter) {
    getters[address] = getter;
}

void Memory::registerGetter(u_int16_t start, u_int16_t end, MEMORY_GETTER getter) {
    for(u_int32_t i = start; i <= end; i++) {
        registerGetter(i, getter);
    }
}

void Memory::registerSetter(u_int16_t address, MEMORY_SETTER setter, bool override) {
    std::vector<MEMORY_SETTER>* addressSetters = &this->setters[address];
    
    if(addressSetters->size() == 0 || !override) {
        addressSetters->push_back(setter);
    } else if (override) {
        addressSetters->at(0) = setter;
    }
}

void Memory::registerSetter(u_int16_t start, u_int16_t end, MEMORY_SETTER setter, bool override) {
    for(u_int32_t i = start; i <= end; i++) {
        registerSetter(i, setter, override);
    }
}

void Memory::registerFlagger(MEMORY_FLAGGER flagger) {
    this->flagger = flagger;
}

u_int8_t Memory::get_8(u_int16_t address) {
    return getters[address](address, 255);
}

u_int8_t Memory::get_8(u_int16_t address, u_int8_t bank) {
    return getters[address](address, bank);
}

bool Memory::set_8(u_int16_t address, u_int8_t value) {
    std::vector<MEMORY_SETTER> addressSetters = setters[address];
    bool set = addressSetters[0](address, value);

    if(!set) {
        core.set_8(address, value);
    }
    
    for(u_int8_t i = 1; i < addressSetters.size(); i++) {
        addressSetters[i](address, value);
    }

    return true;
}

bool Memory::set_16(u_int16_t address, u_int16_t value) {
    set_8(address,  Bytes::split_16_lower(value));
    set_8(address + 1, Bytes::split_16_upper(value));
    return true;
}

void Memory::flagInterrupt(u_int8_t bit) {
    flagger(bit);
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
