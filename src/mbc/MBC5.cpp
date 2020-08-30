//
// Created by matthew on 18/07/2020.
//

#include "MBC5.h"
#include "Bytes.h"
#include "MemoryMap.h"

int16_t MBC5::get_8(u_int16_t address, u_int8_t *rom, Ram* ram) {
    if(address >= 0x4000 && address <= 0x7FFF) {
        u_int32_t finalAddress = (romBank * 0x4000) + (address - 0x4000);
        return rom[finalAddress];
    }

    if(address >= 0xA000 && address <= 0xBFFF) {
        if(!ramEnabled) return 0xFF;
        u_int32_t finalAddress = (ramBank * 0x2000) + (address - 0xA000);
        return ram->get_8(finalAddress);
    }

    return -1;
}

bool MBC5::set_8(u_int16_t address, u_int8_t value, u_int8_t *rom, Ram* ram) {
    bool set = true;

    if(address >= 0x0000 && address <= 0x1FFF) {
        ramEnabled = value == 0x0A;
    } else if (address >= 0x2000 && address <= 0x2FFF) {
        romBank = (romBank & 0x100) | (value & 0xFF);
    } else if (address >= 0x3000 && address <= 0x3FFF) {
        romBank = (romBank & 0x0FF) | ((value & 0x1) << 8);
    } else if (address >= 0x4000 && address <= 0x5FFF) {
        ramBank = value & 0xF;
    } else if (address >= 0xA000 && address <= 0xBFFF) {
        if(!ramEnabled) return false;
        u_int32_t finalAddress = (ramBank * 0x2000) + (address - 0xA000);
        ram->set_8(finalAddress, value);
    } else {
        set = false;
    }

    return set;
}
