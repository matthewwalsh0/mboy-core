//
// Created by matthew on 05/07/2020.
//

#include "Memory.h"
#include "Bytes.h"
#include "MemoryMap.h"

const uint16 ADDRESS_DMA_TRANSFER = 0xFF46;
const uint16 ADDRESS_SPRITE_INFO_START = 0xFE00;

void Memory::init(CoreMemory *coreMemory, Rom *rom, MemoryHook *cpu, MemoryHook *gpu,
        MemoryHook* timer, MemoryHook* apu, MemoryHook* joypad) {
    this->coreMemory = coreMemory;
    this->rom = rom;
    this->cpu = cpu;
    this->gpu = gpu;
    this->timer = timer;
    this->apu = apu;
    this->joypad = joypad;

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
            return vram.get_8(address);
        case 0xA:
        case 0xB:
            return rom->get_8(address);
        case 0xC:
        case 0xD:
            return wram.get_8(address);
        case 0xE:
        case 0xF:
            if(address == ADDRESS_VRAM_BANK) {
                return vram.bank;
            } else if (address == ADDRESS_WRAM_BANK) {
                return wram.getBank();
            } else if(address == ADDRESS_INTERRUPT_ENABLE || address == ADDRESS_INTERRUPT_FLAGS || address == 0xFF4D) {
                return cpu->get_8(address);
            } else if (address >= 0xFF51 && address <= 0xFF55) {
                return gpu->getHDMA(address);
            } else if (address == ADDRESS_JOYPAD) {
                return joypad->get_8(address);
            } else if (address >= 0xFF04 && address <= 0xFF07) {
                return timer->get_8(address);
            } else if (address == ADDRESS_STAT || address == ADDRESS_TARGET_LINE || address == ADDRESS_LINE || address == 0xFF69 || address == 0xFF6A) {
                return gpu->get_8(address);
            }
        default:
            return coreMemory->get_8(address);
    }
}

void Memory::set_8(uint16 address, uint8 value) {
    if((address >= 0x0000 && address <= 0x7FFF)  || (address >= 0xA000 && address <= 0xBFFF)) {
        rom->set_8(address, value);
        return;
    } else if (address == ADDRESS_VRAM_BANK) {
        vram.setBank(value);
        return;
    } else if (address >= ADDRESS_VRAM_START && address <= ADDRESS_VRAM_END) {
        vram.set_8(address, value);
        gpu->set_8(address, value);
        return;
    } else if (address == ADDRESS_WRAM_BANK) {
        wram.setBank(value);
        return;
    } else if (address >= ADDRESS_WRAM_START && address <= ADDRESS_WRAM_END) {
        wram.set_8(address, value);
        return;
    } else if (address >= 0xFF04 && address <= 0xFF07) {
        timer->set_8(address, value);
        return;
    } else if (address == ADDRESS_DMA_TRANSFER) {
        dma(value);
        return;
    } else if (address >= 0xFF51 && address <= 0xFF55) {
        gpu->setHDMA(address, value);
        return;
    } else if (address == LCD_CONTROL || address == ADDRESS_STAT || address == ADDRESS_TARGET_LINE || address == ADDRESS_LINE || address == 0xFF68 || address == 0xFF69 || address == 0xFF6A || address == 0xFF6B) {
        coreMemory->set_8(address, value);
        gpu->set_8(address, value);
        return;
    } else if (address >= TILE_SET_1_START && address < TILE_SET_0_END) {
        coreMemory->set_8(address, value);
        gpu->set_8(address, value);
    } else if (address == ADDRESS_INTERRUPT_ENABLE || address == ADDRESS_INTERRUPT_FLAGS || address == 0xFF4D) {
        cpu->set_8(address, value);
        return;
    } else if (address == ADDRESS_JOYPAD) {
        joypad->set_8(address, value);
    } else if (address >= SQUARE_1_ADDRESS_START && address < SQUARE_1_ADDRESS_START + 4) {
        apu->set_8(address, value);
    } else if (address >= SQUARE_2_ADDRESS_START && address < SQUARE_2_ADDRESS_START + 4) {
        apu->set_8(address, value);
    } else if (address >= WAVE_START && address < WAVE_START + 5) {
        apu->set_8(address, value);
    } else if (address == 0xFF26) {
        apu->set_8(address, value);
        return;
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

