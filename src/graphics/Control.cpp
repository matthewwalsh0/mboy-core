//
// Created by matthew on 05/07/2020.
//

#include "Control.h"
#include "Bytes.h"
#include "MemoryMap.h"

Control::Control(uint8 value) {
    background = Bytes::getBit_8(value, 0);
    sprites = Bytes::getBit_8(value, 1);
    largeSprites = Bytes::getBit_8(value, 2);
    alternateBackgroundTileMap = Bytes::getBit_8(value, 3);
    alternateBackgroundTileSet = Bytes::getBit_8(value, 4);
    window = Bytes::getBit_8(value, 5);
    alternateWindowTileMap = Bytes::getBit_8(value, 6);
    display = Bytes::getBit_8(value, 7);
}

Control::Control(MemoryHook *memory) {
    Control(memory->get_8(LCD_CONTROL));
}
