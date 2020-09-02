#include "WRAM.h"
#include "MemoryMap.h"
#include "WRAM.h"
#include "MemoryRegister.h"

WRAM::WRAM(MemoryRegister* memory) {
    memory->registerGetter(0xC000, 0xDFFF, (MemoryHook*) this);
    memory->registerGetter(ADDRESS_WRAM_BANK, (MemoryHook*) this);

    memory->registerSetter(0xC000, 0xDFFF, (MemoryHook*) this);
    memory->registerSetter(ADDRESS_WRAM_BANK, (MemoryHook*) this);
}

u_int8_t WRAM::getBank() {
    return bank;
}

void WRAM::setBank(u_int8_t value) {
    u_int8_t tempBank = value & 0b111;
    this->bank = tempBank == 0 ? 1 : tempBank;
}

u_int8_t WRAM::get_8(u_int16_t address) {
    if(address == ADDRESS_WRAM_BANK) {
        return getBank();
    }

    if(address <= ADDRESS_WRAM_BANK_0_END) {
        u_int16_t relative = address - ADDRESS_WRAM_START;
        return data[0][relative];
    } else {
        u_int16_t relative = address - (ADDRESS_WRAM_BANK_0_END + 1);
        return data[bank][relative];
    }
}

bool WRAM::set_8(u_int16_t address, u_int8_t value) {
    if(address == ADDRESS_WRAM_BANK) {
        setBank(value);
        return true;
    } else if(address <= ADDRESS_WRAM_BANK_0_END) {
        u_int16_t relative = address - ADDRESS_WRAM_START;
        data[0][relative] = value;
        return true;
    } else {
        u_int16_t relative = address - (ADDRESS_WRAM_BANK_0_END + 1);
        data[bank][relative] = value;
        return true;
    }
}
