//
// Created by matthew on 05/07/2020.
//

#include "GPU.h"
#include "MemoryMap.h"
#include "Types.h"
#include "Bytes.h"

const uint8 MODE_HORIZONTAL_BLANK = 0;
const uint8 MODE_VERTICAL_BLANK = 1;
const uint8 MODE_SCANLINE_SPRITE = 2;
const uint8 MODE_SCANLINE_BACKGROUND = 3;
const uint16 DURATION_SCANLINE_SPRITE = 80;
const uint16 DURATION_SCANLINE_BACKGROUND = 172;
const uint16 DURATION_HORIZONTAL_BLANK = 204;
const uint16 DURATION_VERTICAL_BLANK = 456;
const std::string LOG_PATH = "/sdcard/Download/matterboy_log_gpu.txt";

const uint16 MODE_DURATIONS[] = {
        DURATION_HORIZONTAL_BLANK,
        DURATION_VERTICAL_BLANK,
        DURATION_SCANLINE_SPRITE,
        DURATION_SCANLINE_BACKGROUND};

GPU::GPU(Memory *memory, GUI* gui) :
pixels(SCREEN_WIDTH, SCREEN_HEIGHT),
display(memory),
logFile(LOG_PATH) {
    this->memory = memory;
    this->control = new Control((uint8) 0);
    this->gui = gui;

    mode = 0;
    cycleCount = 0;
    line = 0;
    coincidenceInterrupt = false;
    oamInterrupt = false;
    vblankInterrupt = false;
    hblankInterrupt = false;
    coincidenceLine = 0;
}

void GPU::step(uint16 lastInstructionDuration, Memory *memory, bool isColour, uint32 count) {
    if(!control->display) { return; }

    for(uint16 i = 0; i < lastInstructionDuration; i++) {
        if(cycleCount >= MODE_DURATIONS[mode]) {
            switch (mode) {
                case MODE_HORIZONTAL_BLANK:
                    cycleCount = 0;
                    line += 1;

                    if(coincidenceInterrupt && line == coincidenceLine) {
                        memory->flag_interrupt(INTERRUPT_BIT_LCD_STAT);
                    }

                    if(line == SCREEN_HEIGHT) {
                        mode = MODE_VERTICAL_BLANK;

                        gui->displayBuffer(pixels.data);
                        frameCount += 1;

                        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                        uint32 duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

                        if(duration > 1000) {
                            gui->displayFPS(frameCount);
                            frameCount = 0;
                            begin = std::chrono::steady_clock::now();
                        }

                        memory->flag_interrupt(INTERRUPT_BIT_VERTICAL_BLANK);

                        if(vblankInterrupt) {
                            memory->flag_interrupt(INTERRUPT_BIT_LCD_STAT);
                        }
                    } else {
                        mode = MODE_SCANLINE_SPRITE;
                    }
                    break;
                case MODE_VERTICAL_BLANK:
                    line += 1;
                    cycleCount = 0;

                    if(line > 153) {
                        mode = MODE_SCANLINE_SPRITE;
                        line = 0;

                        if (oamInterrupt) {
                            memory->flag_interrupt(INTERRUPT_BIT_LCD_STAT);
                        }
                    }
                    break;
                case MODE_SCANLINE_SPRITE:
                    mode = MODE_SCANLINE_BACKGROUND;
                    cycleCount = 0;
                    break;
                case MODE_SCANLINE_BACKGROUND:
                    mode = MODE_HORIZONTAL_BLANK;
                    cycleCount = 0;

                    display.drawLine(&pixels, line, isColour, control);

                    if(hblankInterrupt) {
                        memory->flag_interrupt(INTERRUPT_BIT_LCD_STAT);
                    }
                    break;
            }
        }

        cycleCount += 1;
    }

    //logFile.write("%d - %d - %d - %d - %d", count, mode, cycleCount, line, coincidenceLine);
}

uint8 GPU::getStat() {
    uint8 lcdStat = 0;

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

void GPU::setStat(uint8 value) {
    hblankInterrupt = Bytes::getBit_8(value, 3);
    vblankInterrupt = Bytes::getBit_8(value, 4);
    oamInterrupt = Bytes::getBit_8(value, 5);
    coincidenceInterrupt = Bytes::getBit_8(value, 6);
}

void GPU::setControl(uint8 value) {
    Control* current = this->control;
    delete current;

    control = new Control(value);

    if(!control->display) {
        line = 0;
        mode = 0;
    }
}

uint8 GPU::get_8(uint16 address) {
    switch(address) {
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

bool GPU::set_8(uint16 address, uint8 value) {
    if(address >= TILE_SET_1_START && address < TILE_SET_0_END) {
        display.set_8(address, value);
        return true;
    } else {
        switch (address) {
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
                throw std::invalid_argument("Invalid write on GPU.");
        }
    }
}