//
// Created by matthew on 05/07/2020.
//

#include "Memory.h"
#include "Bytes.h"
#include "MemoryMap.h"

const u_int16_t ADDRESS_DMA_TRANSFER = 0xFF46;
const u_int16_t ADDRESS_SPRITE_INFO_START = 0xFE00;

void Memory::init(CoreMemory *coreMemory, Rom *rom, CPU *cpu, GPU *gpu,
        Timer* timer, APU* apu, Joypad* joypad) {
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

u_int8_t Memory::get_8(u_int16_t address) {
    u_int8_t nibble_1 = (address & 0xF000) >> 12;

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
            return 0;
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

u_int8_t Memory::get_8(u_int16_t address, u_int8_t bank) {
    u_int8_t nibble_1 = (address & 0xF000) >> 12;

    switch(nibble_1) {
        case 8:
        case 9:
            return vram.get_8(address, bank);
        default:
            return 0;
    }
}

u_int8_t Memory::get_core_8(u_int16_t address) {
    return coreMemory->get_8(address);
}

bool Memory::set_8(u_int16_t address, u_int8_t value) {
    if((address >= 0x0000 && address <= 0x7FFF)  || (address >= 0xA000 && address <= 0xBFFF)) {
        rom->set_8(address, value);
        return true;
    } else if (address == ADDRESS_VRAM_BANK) {
        vram.setBank(value);
        return true;
    } else if (address >= ADDRESS_VRAM_START && address <= ADDRESS_VRAM_END) {
        vram.set_8(address, value);
        gpu->set_8(address, value);
        return true;
    } else if (address == ADDRESS_WRAM_BANK) {
        wram.setBank(value);
        return true;
    } else if (address >= ADDRESS_WRAM_START && address <= ADDRESS_WRAM_END) {
        wram.set_8(address, value);
        return true;
    } else if (address >= 0xFF04 && address <= 0xFF07) {
        timer->set_8(address, value);
        return true;
    } else if (address == ADDRESS_DMA_TRANSFER) {
        dma(value);
        return true;
    } else if (address >= 0xFF51 && address <= 0xFF55) {
        gpu->setHDMA(address, value);
        return true;
    } else if (address == LCD_CONTROL || address == ADDRESS_STAT || address == ADDRESS_TARGET_LINE || address == ADDRESS_LINE || address == 0xFF68 || address == 0xFF69 || address == 0xFF6A || address == 0xFF6B) {
        coreMemory->set_8(address, value);
        gpu->set_8(address, value);
        return true;
    } else if (address >= TILE_SET_1_START && address < TILE_SET_0_END) {
        coreMemory->set_8(address, value);
        gpu->set_8(address, value);
    } else if (address == ADDRESS_INTERRUPT_ENABLE || address == ADDRESS_INTERRUPT_FLAGS || address == 0xFF4D) {
        cpu->set_8(address, value);
        return true;
    } else if (address == ADDRESS_JOYPAD) {
        joypad->set_8(address, value);
    } else if (address >= SQUARE_1_ADDRESS_START && address < SQUARE_1_ADDRESS_START + 4) {
        apu->set_8(address, value);
    } else if (address >= SQUARE_2_ADDRESS_START && address < SQUARE_2_ADDRESS_START + 4) {
        apu->set_8(address, value);
    } else if (address >= WAVE_START && address < WAVE_START + 5) {
        apu->set_8(address, value);
    } else if (address >= 0xFF20 && address <= 0xFF23) {
        apu->set_8(address, value);
        coreMemory->set_8(address, value);
    } else if (address == 0xFF26) {
        apu->set_8(address, value);
        return true;
    } else if (address >= SPRITE_INFO_START && address < SPRITE_INFO_END) {
        coreMemory->set_8(address, value);
        gpu->display.clearSprite(address);
        return true;
    }

    coreMemory->set_8(address, value);
    return true;
}

bool Memory::set_16(u_int16_t address, u_int16_t value) {
    set_8(address,  Bytes::split_16_lower(value));
    set_8(address + 1, Bytes::split_16_upper(value));
    return true;
}

void Memory::flagInterrupt(u_int8_t bit) {
    cpu->flagInterrupt(bit);
}

void Memory::dma(u_int8_t value) {
    u_int16_t start = Bytes::join_8(value, 0x00);
    u_int16_t end = Bytes::join_8(value, 0x9F) + 1;

    for(u_int16_t sourceAddress = start; sourceAddress < end; sourceAddress++) {
        u_int16_t relative = sourceAddress - start;
        u_int16_t targetAddress = ADDRESS_SPRITE_INFO_START + relative;
        u_int8_t sourceValue = get_8(sourceAddress);
        set_8(targetAddress, sourceValue);
    }
}

