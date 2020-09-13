#include "VRAM.h"

#include "MemoryMap.h"

VRAM::VRAM(MemoryRegister* memory) {
    memory->registerGetter(ADDRESS_VRAM_START, ADDRESS_VRAM_END, [this]MEMORY_GETTER_LAMBDA {
        if(bank == 255) { bank = this->bank; }
        u_int16_t relative = address - ADDRESS_VRAM_START;
        return data[bank * VRAM_BANK_SIZE + relative];
    });

    memory->registerGetter(ADDRESS_VRAM_BANK, [this]MEMORY_GETTER_LAMBDA {
        return this->bank;
    });

    memory->registerSetter(ADDRESS_VRAM_START, ADDRESS_VRAM_END, [this]MEMORY_SETTER_LAMBDA {
        u_int16_t relative = address - ADDRESS_VRAM_START;
        data[this->bank * VRAM_BANK_SIZE + relative] = value;
        return true;
    });

    memory->registerSetter(ADDRESS_VRAM_BANK, [this]MEMORY_SETTER_LAMBDA {
        this->bank = value & 0x1;
        return true;
    });
}
