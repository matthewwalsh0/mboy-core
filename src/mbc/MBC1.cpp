//
// Created by matthew on 22/08/2020.
//

#include "MBC1.h"
#include "Bytes.h"
#include "MemoryMap.h"

static u_int8_t getRomBank(u_int8_t bank) {
    u_int8_t finalBank = bank;

    if(bank == 0x0 || bank == 0x20 || bank == 0x40 || bank == 0x60) {
        finalBank += 1;
    }

    return finalBank;
}

int16_t MBC1::get_8(u_int16_t address, u_int8_t *rom, Ram* ram) {
    if(address >= 0x4000 && address <= 0x7FFF) {
        u_int32_t finalAddress = (romBank * 0x4000) + (address - 0x4000);
        return rom[finalAddress];
    }

    if(address >= 0xA000 && address <= 0xBFFF) {
        u_int32_t finalAddress = (ramBank * 0x2000) + (address - 0xA000);
        return ram->get_8(finalAddress);
    }

    return -1;
}

bool MBC1::set_8(u_int16_t address, u_int8_t value, u_int8_t *rom, Ram* ram) {
    bool set = true;

    if(address >= MBC1_ENABLE_EXTERNAL_RAM_START && address <= MBC1_ENABLE_EXTERNAL_RAM_END) {
        ramEnabled = (value & 0x0F) == 0x0A;
    } else if (address >= MBC1_MODE_START && address <= MBC1_MODE_END) {
        ramMode = (value & 0x1) == 0x1;
    } else if(address >= MBC1_ROM_BANK_LOW_START && address <= MBC1_ROM_BANK_LOW_END) {
        u_int8_t newRomBank = (romBank & 0x60) + (value & 0x1F);
        romBank = getRomBank(newRomBank);
    } else if (address >= MBC1_ROM_BANK_HIGH_START && address <= MBC1_ROM_BANK_HIGH_END) {
        if(ramMode) {
            ramBank = value & 0x3;
        } else {
            u_int8_t newRomBank = (romBank & 0x1F) + ((value & 0x3) << 5);
            romBank = getRomBank(newRomBank);
        }
    } else if (address >= 0xA000 && address <= 0xBFFF) {
        int finalAddress = (ramBank * 0x2000) + (address - 0xA000);
        ram->set_8(finalAddress, value);
    } else {
        set = false;
    }

    return set;
}
