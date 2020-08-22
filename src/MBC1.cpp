//
// Created by matthew on 22/08/2020.
//

#include "MBC1.h"
#include "Bytes.h"
#include "MemoryMap.h"

static uint8 getRomBank(uint8 bank) {
    uint8 finalBank = bank;

    if(bank == 0x0 || bank == 0x20 || bank == 0x40 || bank == 0x60) {
        finalBank += 1;
    }

    return finalBank;
}

int16 MBC1::get_8(uint16 address, uint8 *rom, Ram* ram) {
    if(address >= 0x4000 && address <= 0x7FFF) {
        uint32 finalAddress = (romBank * 0x4000) + (address - 0x4000);
        return rom[finalAddress];
    }

    if(address >= 0xA000 && address <= 0xBFFF) {
        uint32 finalAddress = (ramBank * 0x2000) + (address - 0xA000);
        return ram->get_8(finalAddress);
    }

    return -1;
}

bool MBC1::set_8(uint16 address, uint8 value, uint8 *rom, Ram* ram) {
    bool set = true;

    if(address >= MBC1_ENABLE_EXTERNAL_RAM_START && address <= MBC1_ENABLE_EXTERNAL_RAM_END) {
        ramEnabled = (value & 0x0F) == 0x0A;
    } else if (address >= MBC1_MODE_START && address <= MBC1_MODE_END) {
        ramMode = (value & 0x1) == 0x1;
    } else if(address >= MBC1_ROM_BANK_LOW_START && address <= MBC1_ROM_BANK_LOW_END) {
        uint8 newRomBank = (romBank & 0x60) + (value & 0x1F);
        romBank = getRomBank(newRomBank);
    } else if (address >= MBC1_ROM_BANK_HIGH_START && address <= MBC1_ROM_BANK_HIGH_END) {
        if(ramMode) {
            ramBank = value & 0x3;
        } else {
            uint8 newRomBank = (romBank & 0x1F) + ((value & 0x3) << 5);
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
