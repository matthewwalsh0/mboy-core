//
// Created by matthew on 29/07/2020.
//

#include "WRAM.h"
#include "MemoryMap.h"
#include "WRAM.h"


uint8 WRAM::getBank() {
    return bank;
}

void WRAM::setBank(uint8 value) {
    uint8 tempBank = value & 0b111;
    this->bank = tempBank == 0 ? 1 : tempBank;
}

uint8 WRAM::get_8(uint16 address) {
    if(address <= ADDRESS_WRAM_BANK_0_END) {
        uint16 relative = address - ADDRESS_WRAM_START;
        return data[0][relative];
    } else {
        uint16 relative = address - (ADDRESS_WRAM_BANK_0_END + 1);
        return data[bank][relative];
    }
}

void WRAM::set_8(uint16 address, uint8 value) {
    if(address <= ADDRESS_WRAM_BANK_0_END) {
        uint16 relative = address - ADDRESS_WRAM_START;
        data[0][relative] = value;
        return;
    } else {
        uint16 relative = address - (ADDRESS_WRAM_BANK_0_END + 1);
        data[bank][relative] = value;
        return;
    }
}
