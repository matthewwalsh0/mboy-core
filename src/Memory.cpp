//
// Created by matthew on 05/07/2020.
//

#include "Memory.h"
#include "Bytes.h"
#include "MemoryMap.h"

const uint16 ADDRESS_DMA_TRANSFER = 0xFF46;
const uint16 ADDRESS_SPRITE_INFO_START = 0xFE00;

void Memory::init(CoreMemory *coreMemory, Rom *rom, MemoryHook *cpu, MemoryHook *gpu,
        MemoryHook* timer, MemoryHook* apu) {
    this->coreMemory = coreMemory;
    this->rom = rom;
    this->cpu = cpu;
    this->gpu = gpu;
    this->timer = timer;
    this->apu = apu;

    set_8(LCD_CONTROL, 0x91);
    set_8(ADDRESS_JOYPAD, 0x0F);
}

uint8 Memory::get_8(uint16 address) {
    uint8 nibble_1 = (address & 0xF000) >> 12;

    switch(nibble_1) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            return rom->get_8(address);
        case 8:
        case 9:
        case 0xA:
        case 0xB:
        case 0xC:
        case 0xD:
        case 0xE:
        case 0xF:
            if(address == ADDRESS_INTERRUPT_ENABLE || address == ADDRESS_INTERRUPT_FLAGS) {
                return cpu->get_8(address);
            } else if (address == ADDRESS_JOYPAD) {
                return column | 0x0F;
            } else if (address >= 0xFF04 && address <= 0xFF07) {
                return timer->get_8(address);
            } else if (address == ADDRESS_STAT || address == ADDRESS_TARGET_LINE || address == ADDRESS_LINE) {
                return gpu->get_8(address);
            }
        default:
            return coreMemory->get_8(address);
    }
}

void Memory::set_8(uint16 address, uint8 value) {
    if((address >= 0x0000 && address <= 0x7FFF)) {
        rom->set_8(address, value);
        return;
    } else if (address >= 0xFF04 && address <= 0xFF07) {
        timer->set_8(address, value);
        return;
    } else if (address == ADDRESS_DMA_TRANSFER) {
        dma(value);
        return;
    } else if (address == LCD_CONTROL || address == ADDRESS_STAT || address == ADDRESS_TARGET_LINE || address == ADDRESS_LINE) {
        coreMemory->set_8(address, value);
        gpu->set_8(address, value);
        return;
    } else if (address >= TILE_SET_1_START && address < TILE_SET_0_END) {
        coreMemory->set_8(address, value);
        gpu->set_8(address, value);
    } else if (address == ADDRESS_INTERRUPT_ENABLE || address == ADDRESS_INTERRUPT_FLAGS) {
        cpu->set_8(address, value);
        return;
    } else if (address == ADDRESS_JOYPAD) {
        uint8 columnValue = value & 0x30;
        bool column_1 = Bytes::getBit_8(columnValue, 4);
        bool column_2 = Bytes::getBit_8(columnValue, 5);
        column = column_1 ? 0 : column_2 ? 1 : column;
    } else if (address >= SQUARE_1_ADDRESS_START && address < SQUARE_1_ADDRESS_START + 4) {
        apu->set_8(address, value);
    }

    coreMemory->set_8(address, value);
}

void Memory::set_16(uint16 address, uint16 value) {
    set_8(address,  Bytes::split_16_lower(value));
    set_8(address + 1, Bytes::split_16_upper(value));
}

void Memory::flag_interrupt(uint8 bit) {
    cpu->flag_interrupt(bit);
}

void Memory::dma(uint8 value) {
    uint16 start = Bytes::join_8(value, 0x00);
    uint16 end = Bytes::join_8(value, 0x9F) + 1;

    for(uint16 sourceAddress = start; sourceAddress < end; sourceAddress++) {
        uint16 relative = sourceAddress - start;
        uint16 targetAddress = ADDRESS_SPRITE_INFO_START + relative;
        uint8 sourceValue = get_8(sourceAddress);
        set_8(targetAddress, sourceValue);
    }
}

