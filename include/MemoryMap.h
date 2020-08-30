//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_MEMORYMAP_H
#define MY_APPLICATION_MEMORYMAP_H

#include <sys/types.h>

// CPU + Timer
const u_int16_t ADDRESS_DIVIDER = 0xFF04;
const u_int16_t ADDRESS_INTERRUPT_FLAGS = 0xFF0F;
const u_int16_t ADDRESS_INTERRUPT_ENABLE = 0xFFFF;

// GPU
const u_int16_t ADDRESS_COLOUR_FLAG = 0x0143;
const u_int16_t ADDRESS_VRAM_BANK = 0xFF4F;
const u_int16_t ADDRESS_VRAM_START = 0x8000;
const u_int16_t ADDRESS_VRAM_END = 0x9FFF;
const u_int16_t ADDRESS_WRAM_START = 0xC000;
const u_int16_t ADDRESS_WRAM_END = 0xDFFF;
const u_int16_t ADDRESS_WRAM_BANK = 0xFF70;
const u_int16_t ADDRESS_WRAM_BANK_0_END = 0xCFFF;
const u_int16_t TILE_SET_1_START = 0x8000;
const u_int16_t TILE_SET_1_END = 0x8FFF + 1;
const u_int16_t TILE_SET_0_START = 0x8800;
const u_int16_t TILE_SET_0_END = 0x97FF + 1;
const u_int16_t TILE_MAP_0_START = 0x9800;
const u_int16_t TILE_MAP_0_END = 0x9BFF + 1;
const u_int16_t TILE_MAP_1_START = 0x9C00;
const u_int16_t TILE_MAP_1_END = 0x9FFF + 1;
const u_int16_t SPRITE_INFO_START = 0xFE00;
const u_int16_t SPRITE_INFO_END = 0xFE9F + 1;
const u_int16_t LCD_CONTROL = 0xFF40;
const u_int16_t ADDRESS_STAT = 0xFF41;
const u_int16_t SCROLL_Y = 0xFF42;
const u_int16_t SCROLL_X = 0xFF43;
const u_int16_t ADDRESS_LINE = 0xFF44;
const u_int16_t ADDRESS_TARGET_LINE = 0xFF45;
const u_int16_t BACKGROUND_PALETTE = 0xFF47;
const u_int16_t SPRITE_PALETTE_0 = 0xFF48;
const u_int16_t SPRITE_PALETTE_1 = 0xFF49;
const u_int16_t WINDOW_Y = 0xFF4A;
const u_int16_t WINDOW_X = 0xFF4B;

// APU
const u_int16_t SQUARE_1_ADDRESS_START = 0xFF11;
const u_int16_t SQUARE_2_ADDRESS_START = 0xFF16;
const u_int16_t WAVE_TABLE_START = 0xFF30;
const u_int16_t WAVE_START = 0xFF1A;

// Memory Controller
const u_int16_t ADDRESS_TYPE = 0x0147;
const u_int16_t MBC1_ENABLE_EXTERNAL_RAM_START = 0x0000;
const u_int16_t MBC1_ENABLE_EXTERNAL_RAM_END = 0x1FFF;
const u_int16_t MBC1_MODE_START = 0x6000;
const u_int16_t MBC1_MODE_END = 0x7FFF;
const u_int16_t MBC1_ROM_BANK_LOW_START = 0x2000;
const u_int16_t MBC1_ROM_BANK_LOW_END = 0x3FFF;
const u_int16_t MBC1_ROM_BANK_HIGH_START = 0x4000;
const u_int16_t MBC1_ROM_BANK_HIGH_END = 0x5FFF;

// Other
const u_int16_t ADDRESS_JOYPAD = 0xFF00;
const u_int8_t INTERRUPT_BIT_VERTICAL_BLANK = 0;
const u_int8_t INTERRUPT_BIT_LCD_STAT = 1;
const u_int8_t INTERRUPT_BIT_TIMER = 2;

#endif //MY_APPLICATION_MEMORYMAP_H
