//
// Created by matthew on 18/07/2020.
//

#include "MBC3.h"
#include "Bytes.h"
#include "MemoryMap.h"

static uint8 getRomBank(uint8 bank) {
    uint8 finalBank = bank;

    if(bank == 0x0) {
        finalBank += 1;
    }

    return finalBank;
}

int16 MBC3::get_8(uint16 address, uint8 *rom, uint8* ram) {
    if(address >= 0x4000 && address <= 0x7FFF) {
        uint32 finalAddress = (romBank * 0x4000) + (address - 0x4000);
        return rom[finalAddress];
    }

    if(address >= 0xA000 && address <= 0xBFFF) {
        if(ramBank > -1) {
            uint32 finalAddress = (ramBank * 0x2000) + (address - 0xA000);
            return ram[finalAddress];
        } else {
            return 0;
        }
    }

    return -1;
}

bool MBC3::set_8(uint16 address, uint8 value, uint8 *rom, uint8* ram) {
    bool set = true;

    if(address >= MBC1_ENABLE_EXTERNAL_RAM_START && address <= MBC1_ENABLE_EXTERNAL_RAM_END) {
        ramEnabled = (value & 0x0F) == 0x0A;
    } else if (address >= MBC1_ROM_BANK_LOW_START && address <= MBC1_ROM_BANK_LOW_END) {
        uint8 tempRomBank = Bytes::clearBit_8(value, 7);
        romBank = getRomBank(tempRomBank);
    } else if (address >= MBC1_ROM_BANK_HIGH_START && address <= MBC1_ROM_BANK_HIGH_END) {
        if(value <= 0x07) {
            ramBank = value;
        } else if (value >= 0x08 && value <= 0x0C) {
            ramBank = -1;
        }
    } else if (address >= 0xA000 && address <= 0xBFFF) {
        if(ramBank > -1) {
            uint32 finalAddress = (ramBank * 0x2000) + (address - 0xA000);
            ram[finalAddress] = value;
        }
    } else {
        set = false;
    }

    return set;
}
