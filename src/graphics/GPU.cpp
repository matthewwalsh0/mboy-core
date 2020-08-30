//
// Created by matthew on 05/07/2020.
//

#include "GPU.h"
#include "MemoryMap.h"
#include <sys/types.h>
#include "Bytes.h"

const u_int8_t MODE_HORIZONTAL_BLANK = 0;
const u_int8_t MODE_VERTICAL_BLANK = 1;
const u_int8_t MODE_SCANLINE_SPRITE = 2;
const u_int8_t MODE_SCANLINE_BACKGROUND = 3;
const u_int16_t DURATION_SCANLINE_SPRITE = 80;
const u_int16_t DURATION_SCANLINE_BACKGROUND = 172;
const u_int16_t DURATION_HORIZONTAL_BLANK = 204;
const u_int16_t DURATION_VERTICAL_BLANK = 456;
const std::string LOG_PATH = "/sdcard/Download/matterboy_log_gpu.txt";

const u_int16_t MODE_DURATIONS[] = {
        DURATION_HORIZONTAL_BLANK,
        DURATION_VERTICAL_BLANK,
        DURATION_SCANLINE_SPRITE,
        DURATION_SCANLINE_BACKGROUND};

GPU::GPU(MemoryHook *memory, GUI* gui, struct config* config) :
pixels(SCREEN_WIDTH, SCREEN_HEIGHT),
logFile(LOG_PATH),
display(memory, config) {
    this->memory = memory;
    this->control = new Control((u_int8_t) 0);
    this->gui = gui;
    this->config = config;

    mode = 0;
    cycleCount = 0;
    line = 0;
    coincidenceInterrupt = false;
    oamInterrupt = false;
    vblankInterrupt = false;
    hblankInterrupt = false;
    coincidenceLine = 0;
}

void GPU::step(u_int16_t lastInstructionDuration, MemoryHook *memory, bool isColour, u_int32_t count) {
    if(!control->display) { return; }

    u_int16_t newCycleCount = cycleCount += lastInstructionDuration;
    u_int16_t targetCycleCount = MODE_DURATIONS[mode];

    if(newCycleCount >= targetCycleCount) {
        switch (mode) {
            case MODE_HORIZONTAL_BLANK:
                line += 1;

                if(coincidenceInterrupt && line == coincidenceLine) {
                    memory->flagInterrupt(INTERRUPT_BIT_LCD_STAT);
                }

                if(line == SCREEN_HEIGHT) {
                    mode = MODE_VERTICAL_BLANK;

                    gui->displayBuffer(pixels.data);
                    frameCount += 1;

                    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                    u_int32_t duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

                    if(duration > 1000) {
                        gui->displayFPS(frameCount);
                        frameCount = 0;
                        begin = std::chrono::steady_clock::now();
                    }

                    memory->flagInterrupt(INTERRUPT_BIT_VERTICAL_BLANK);

                    if(vblankInterrupt) {
                        memory->flagInterrupt(INTERRUPT_BIT_LCD_STAT);
                    }
                } else {
                    mode = MODE_SCANLINE_SPRITE;
                }
                break;
            case MODE_VERTICAL_BLANK:
                line += 1;

                if(line > 153) {
                    mode = MODE_SCANLINE_SPRITE;
                    line = 0;

                    if (oamInterrupt) {
                        memory->flagInterrupt(INTERRUPT_BIT_LCD_STAT);
                    }
                }
                break;
            case MODE_SCANLINE_SPRITE:
                mode = MODE_SCANLINE_BACKGROUND;
                break;
            case MODE_SCANLINE_BACKGROUND:
                mode = MODE_HORIZONTAL_BLANK;

                display.drawLine(&pixels, line, isColour, control);

                if(hblankInterrupt) {
                    memory->flagInterrupt(INTERRUPT_BIT_LCD_STAT);
                }
                break;
        }

        newCycleCount = newCycleCount - targetCycleCount;
    }

    cycleCount = newCycleCount;
}

u_int8_t GPU::getStat() {
    u_int8_t lcdStat = 0;

    if (mode == MODE_VERTICAL_BLANK) {
        lcdStat = Bytes::setBit_8(lcdStat, 0);
    } else if (mode == MODE_SCANLINE_SPRITE) {
        lcdStat = Bytes::setBit_8(lcdStat, 1);
    } else if (mode == MODE_SCANLINE_BACKGROUND) {
        lcdStat = Bytes::setBit_8(lcdStat, 0);
        lcdStat = Bytes::setBit_8(lcdStat, 1);
    }

    if(line == coincidenceLine) {
        lcdStat = Bytes::setBit_8(lcdStat, 2);
    }

    if(hblankInterrupt) {
        lcdStat = Bytes::setBit_8(lcdStat, 3);
    }

    if(vblankInterrupt) {
        lcdStat = Bytes::setBit_8(lcdStat, 4);
    }

    if(oamInterrupt) {
        lcdStat = Bytes::setBit_8(lcdStat, 5);
    }

    if(coincidenceInterrupt) {
        lcdStat = Bytes::setBit_8(lcdStat, 6);
    }

    return lcdStat;
}

void GPU::setStat(u_int8_t value) {
    hblankInterrupt = Bytes::getBit_8(value, 3);
    vblankInterrupt = Bytes::getBit_8(value, 4);
    oamInterrupt = Bytes::getBit_8(value, 5);
    coincidenceInterrupt = Bytes::getBit_8(value, 6);
}

void GPU::setControl(u_int8_t value) {
    Control* current = this->control;
    delete current;

    control = new Control(value);

    if(!control->display) {
        line = 0;
        mode = 0;
    }
}

u_int8_t GPU::get_8(u_int16_t address) {
    switch(address) {
        case 0xFF69:
            return display.get_8(address);
        case 0xFF6A:
            return display.get_8(address);
        case ADDRESS_STAT:
            return getStat();
        case ADDRESS_TARGET_LINE:
            return coincidenceLine;
        case ADDRESS_LINE:
            return line;
        default:
            throw std::invalid_argument("Invalid read from GPU.");
    }
}

bool GPU::set_8(u_int16_t address, u_int8_t value) {
    if(address >= TILE_SET_1_START && address < TILE_MAP_1_END) {
        display.set_8(address, value);
        return true;
    } else {
        switch (address) {
            case 0xFF68:
                display.set_8(address, value);
                return true;
            case 0xFF69:
                display.set_8(address, value);
                return true;
            case 0xFF6A:
                display.set_8(address, value);
                return true;
            case 0xFF6B:
                display.set_8(address, value);
                return true;
            case LCD_CONTROL:
                setControl(value);
                return true;
            case ADDRESS_STAT:
                setStat(value);
                return true;
            case ADDRESS_TARGET_LINE:
                coincidenceLine = value;
                return true;
            case ADDRESS_LINE:
                line = 0;
                return true;
            default:
                return false;
        }
    }
}

u_int8_t GPU::getHDMA(u_int16_t address) {
    u_int16_t relative = address - 0xFF51;
    u_int8_t value = 0;

    switch(relative) {
        case 0:
            return hdmaSource & 0xFF00;
        case 1:
            return hdmaSource & 0x00F0;
        case 2:
            return hdmaTarget & 0xFF00;
        case 3:
            return hdmaTarget & 0x00FF;
        case 4:
            value = Bytes::setBit_8(value, 7);
            return value;
        default:
            return 0;
    }
}

void GPU::setHDMA(u_int16_t address, u_int8_t value) {
    u_int16_t relative = address - 0xFF51;

    switch(relative) {
        case 0:
            hdmaSource = (hdmaSource & 0x00FF) | (value << 8);
            return;
        case 1:
            hdmaSource = (hdmaSource & 0xFF00) | (value & 0xF0);
            return;
        case 2:
            hdmaTarget = (hdmaTarget & 0x00FF) | ((value & 0b11111) << 8);
            return;
        case 3:
            hdmaTarget = (hdmaTarget & 0xFF00) | (value & 0xF0);
            return;
        case 4:
            u_int8_t length = value & 0b1111111;
            u_int16_t size = (length + 1) * 0x10;
            bool hblank = Bytes::getBit_8(value, 7);

            if(!hblank) {
                for(int i = 0; i < size; i++) {
                    u_int16_t target = hdmaTarget + i + 0x8000;
                    u_int16_t source = hdmaSource + i;
                    u_int16_t current = memory->get_8(source);
                    memory->set_8(target, current);
                }
            }
            return;
    }
}
