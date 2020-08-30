//
// Created by matthew on 18/07/2020.
//

#include "MBC3.h"
#include "Bytes.h"
#include "MemoryMap.h"

static u_int8_t getRomBank(u_int8_t bank) {
    u_int8_t finalBank = bank;

    if(bank == 0x0) {
        finalBank += 1;
    }

    return finalBank;
}

int16_t MBC3::get_8(u_int16_t address, u_int8_t *rom, Ram* ram) {
    if(address >= 0x4000 && address <= 0x7FFF) {
        u_int32_t finalAddress = (romBank * 0x4000) + (address - 0x4000);
        return rom[finalAddress];
    }

    if(address >= 0xA000 && address <= 0xBFFF) {
        if(ramBank > -1) {
            u_int32_t finalAddress = (ramBank * 0x2000) + (address - 0xA000);
            return ram->get_8(finalAddress);
        } else {
            return 0;
        }
    }

    return -1;
}

bool MBC3::set_8(u_int16_t address, u_int8_t value, u_int8_t *rom, Ram* ram) {
    bool set = true;

    if(address >= MBC1_ENABLE_EXTERNAL_RAM_START && address <= MBC1_ENABLE_EXTERNAL_RAM_END) {
        ramEnabled = (value & 0x0F) == 0x0A;
    } else if (address >= MBC1_ROM_BANK_LOW_START && address <= MBC1_ROM_BANK_LOW_END) {
        u_int8_t tempRomBank = Bytes::clearBit_8(value, 7);
        romBank = getRomBank(tempRomBank);
    } else if (address >= MBC1_ROM_BANK_HIGH_START && address <= MBC1_ROM_BANK_HIGH_END) {
        if(value <= 0x07) {
            ramBank = value;
        } else if (value >= 0x08 && value <= 0x0C) {
            ramBank = -1;
        }
    } else if (address >= 0xA000 && address <= 0xBFFF) {
        if(ramBank > -1) {
            u_int32_t finalAddress = (ramBank * 0x2000) + (address - 0xA000);
            ram->set_8(finalAddress, value);
        }
    } else {
        set = false;
    }

    return set;
}
