//
// Created by matthew on 06/07/2020.
//

#include "VRAM.h"
#include "MemoryMap.h"

void VRAM::setBank(u_int8_t value) {
    bank = value & 0x1;
}

u_int8_t VRAM::get_8(u_int16_t address) {
    return get_8(address, bank);
}

u_int8_t VRAM::get_8(u_int16_t address, u_int8_t bank) {
    u_int16_t relative = address - ADDRESS_VRAM_START;
    return data[bank][relative];
}

void VRAM::set_8(u_int16_t address, u_int8_t value) {
    u_int16_t relative = address - ADDRESS_VRAM_START;
    data[bank][relative] = value;
}
