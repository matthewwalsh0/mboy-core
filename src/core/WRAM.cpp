#include "WRAM.h"

#include "MemoryMap.h"
#include "WRAM.h"
#include "MemoryRegister.h"

WRAM::WRAM(MemoryRegister* memory) {
    memory->registerGetter(ADDRESS_WRAM_BANK, [this]MEMORY_GETTER_LAMBDA {
        return getBank();
    });

    memory->registerGetter(ADDRESS_WRAM_START, ADDRESS_WRAM_BANK_0_END, [this]MEMORY_GETTER_LAMBDA {
        u_int16_t relative = address - ADDRESS_WRAM_START;
        return data[0][relative];
    });

    memory->registerGetter(ADDRESS_WRAM_BANK_0_END + 1, ADDRESS_WRAM_END, [this]MEMORY_GETTER_LAMBDA {
        u_int16_t relative = address - (ADDRESS_WRAM_BANK_0_END + 1);
        return data[this->bank][relative];
    });

    memory->registerSetter(ADDRESS_WRAM_BANK, [this]MEMORY_SETTER_LAMBDA {
        setBank(value);
        return true;
    });

    memory->registerSetter(ADDRESS_WRAM_START, ADDRESS_WRAM_BANK_0_END, [this]MEMORY_SETTER_LAMBDA {
        u_int16_t relative = address - ADDRESS_WRAM_START;
        data[0][relative] = value;
        return true;
    });

    memory->registerSetter(ADDRESS_WRAM_BANK_0_END + 1, ADDRESS_WRAM_END, [this]MEMORY_SETTER_LAMBDA {
        u_int16_t relative = address - (ADDRESS_WRAM_BANK_0_END + 1);
        data[bank][relative] = value;
        return true;
    });
}

u_int8_t WRAM::getBank() {
    return bank;
}

void WRAM::setBank(u_int8_t value) {
    u_int8_t tempBank = value & 0b111;
    this->bank = tempBank == 0 ? 1 : tempBank;
}
