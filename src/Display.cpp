//
// Created by matthew on 06/07/2020.
//

#include "Display.h"
#include "MemoryMap.h"
#include "MonochromePalette.h"
#include "Bytes.h"
#include "GPU.h"
#include "Sprite.h"

Display::Display(Memory *memory) :
tileMap_0(memory, TILE_MAP_0_START, TILE_MAP_0_END),
tileMap_1(memory, TILE_MAP_1_START, TILE_MAP_1_END),
tileSet_0(TILE_SET_0_START, true),
tileSet_1(TILE_SET_1_START, false) {
    this->memory = memory;
}

static void drawBackgroundLine(Pixels* pixels, Memory* memory, Control* control,
        TileMap* tileMap, TileSet* tileSet, palette palette, uint8 line, uint16 scrollX, uint16 scrollY) {
    if(!control->background) return;

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
}

static void drawSpriteLine(Pixels* pixels, Memory* memory, Control* control, uint8 line,
        TileSet* tileSet, uint16 scrollX, uint16 scrollY, palette backgroundPalette) {
    if(!control->sprites) return;

    palette spritePalette_0 = MonochromePalette::get(memory->get_8(SPRITE_PALETTE_0));
    palette spritePalette_1 = MonochromePalette::get(memory->get_8(SPRITE_PALETTE_1));

    for(int8 i = 39; i >= 0; i--) {
        uint16 spriteStart = SPRITE_INFO_START + (4 * i);
        Sprite sprite(memory, spriteStart, control->largeSprites);

        if(sprite.y == 0 && sprite.x == 0) continue;

        uint16 spriteYStart = sprite.y - 16;
        uint16 spriteYEnd = control->largeSprites ? spriteYStart + 16 : spriteYStart + 8;

        if(line >= spriteYStart && line < spriteYEnd) {
            uint16 localY = line - spriteYStart;
            sprite.drawLine(pixels, tileSet, scrollX, scrollY, localY,
                    backgroundPalette, spritePalette_0, spritePalette_1);
        }
    }
}

void Display::drawLine(Pixels *pixels, uint8 line, bool isColour, Control *control) {
    TileSet* tileSet = !control->alternateBackgroundTileSet ? &tileSet_0 : &tileSet_1;
    TileMap* tileMap = !control->alternateBackgroundTileMap ? &tileMap_0 : &tileMap_1;
    palette backgroundMonochromePalette = MonochromePalette::get(memory->get_8(BACKGROUND_PALETTE));
    uint16 scrollX = memory->coreMemory->get_8(SCROLL_X);
    uint16 scrollY = memory->coreMemory->get_8(SCROLL_Y);;

    drawBackgroundLine(pixels, memory, control, tileMap, tileSet, backgroundMonochromePalette, line, scrollX, scrollY);
    drawSpriteLine(pixels, memory, control, line, tileSet, scrollX, scrollY, backgroundMonochromePalette);
}

uint8 Display::get_8(uint16 address) {
    throw std::invalid_argument("Invalid read from display.");
}

static void invalidateTile(TileMap* tileMap, uint16 address) {
    uint16 index = address - tileMap->start;
    int tileIndexY = index / TILE_COUNT;
    int tileIndexX = index % TILE_COUNT;
    tileMap->invalidateTile(tileIndexX, tileIndexY);
}

bool Display::set_8(uint16 address, uint8 value) {
    if(address >= TILE_SET_0_START && address < TILE_SET_0_END) {
        tileSet_0.clearCache();
        tileMap_0.invalidateAllTiles();
        tileMap_1.invalidateAllTiles();
    }
    
    if(address >= TILE_SET_1_START && address < TILE_SET_1_END) {
        tileSet_1.clearCache();
        tileMap_0.invalidateAllTiles();
        tileMap_1.invalidateAllTiles();
    }

    if(address >= TILE_MAP_0_START && address < TILE_MAP_0_END) {
        invalidateTile(&tileMap_0, address);
        return true;
    } else if(address >= TILE_MAP_1_START && address < TILE_MAP_1_END) {
        invalidateTile(&tileMap_1, address);
        return true;
    }

    return true;
}
