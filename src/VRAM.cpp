//
// Created by matthew on 06/07/2020.
//

#include "VRAM.h"
#include "MemoryMap.h"

void VRAM::setBank(uint8 value) {
    bank = value;
}

uint8 VRAM::get_8(uint16 address) {
    return get_8(address, bank);
}

uint8 VRAM::get_8(uint16 address, uint8 bank) {
    uint16 relative = address - ADDRESS_VRAM_START;
    return data[bank][relative];
}

void VRAM::set_8(uint16 address, uint8 value) {
    uint16 relative = address - ADDRESS_VRAM_START;
    data[bank][relative] = value;
}
