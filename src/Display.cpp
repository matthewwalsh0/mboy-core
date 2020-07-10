//
// Created by matthew on 06/07/2020.
//

#include "Display.h"
#include "MemoryMap.h"
#include "MonochromePalette.h"
#include "Bytes.h"
#include "GPU.h"

Display::Display(Memory *memory) :
tileMap_0(memory, TILE_MAP_0_START, TILE_MAP_0_END),
tileMap_1(memory, TILE_MAP_1_START, TILE_MAP_1_END),
tileSet_0(TILE_SET_0_START, true),
tileSet_1(TILE_SET_1_START, false) {
    this->memory = memory;
}

static void drawBackgroundLine(Pixels* pixels, Memory* memory, Control* control,
        TileMap* tileMap, TileSet* tileSet, palette palette, uint8 line) {
    if(!control->background) return;

    uint16 scrollX = memory->coreMemory->get_8(SCROLL_X);
    uint16 scrollY = memory->coreMemory->get_8(SCROLL_Y);;
    uint16 localY = Bytes::wrappingAdd_8(scrollY, line);
    uint16 tileIndexY = localY / TILE_SIZE;
    uint16 scrollIndex = scrollX / TILE_SIZE;
    uint16 lastScrollIndex = scrollIndex + 20;
    int32 scrollWrapIndex = lastScrollIndex > TILE_COUNT ? lastScrollIndex - TILE_COUNT : -1;

    for(uint16 tileIndexX = 0; tileIndexX < TILE_COUNT; tileIndexX++) {
        if(scrollWrapIndex == -1 && (tileIndexX < scrollIndex || tileIndexX > lastScrollIndex)) continue;
        if(scrollWrapIndex != -1 && tileIndexX > scrollWrapIndex && tileIndexX < scrollIndex) continue;

        tileMap->drawTile(tileIndexX, tileIndexY, palette, tileSet);
    }

    uint32* linePixels = tileMap->pixels.getLine(localY, scrollX, SCREEN_WIDTH);
    pixels->setLine(line, linePixels, 0, SCREEN_WIDTH);
    delete linePixels;
}

void Display::drawLine(Pixels *pixels, uint8 line, bool isColour, Control *control) {
    TileSet* tileSet = !control->alternateBackgroundTileSet ? &tileSet_0 : &tileSet_1;
    TileMap* tileMap = !control->alternateBackgroundTileMap ? &tileMap_0 : &tileMap_1;
    palette backgroundMonochromePalette = MonochromePalette::get(memory->get_8(BACKGROUND_PALETTE));

    drawBackgroundLine(pixels, memory, control, tileMap, tileSet, backgroundMonochromePalette, line);
}

uint8 Display::get_8(uint16 address) {
    throw std::invalid_argument("Invalid read from display.");
}

bool Display::set_8(uint16 address, uint8 value) {
    if(address >= TILE_SET_0_START && address < TILE_SET_0_END) {
        tileSet_0.clearCache();
    }
    
    if(address >= TILE_SET_1_START && address < TILE_SET_1_END) {
        tileSet_1.clearCache();
    }

    return true;
}
