//
// Created by matthew on 06/07/2020.
//

#include "Display.h"
#include "MemoryMap.h"
#include "MonochromePalette.h"
#include "Bytes.h"
#include "GPU.h"
#include "Sprite.h"

const uint8 FINAL_INDEX = SCREEN_WIDTH / TILE_SIZE;

Display::Display(Memory *memory, struct config* config) :
tileMap_0(memory, TILE_MAP_0_START, TILE_MAP_0_END),
tileMap_1(memory, TILE_MAP_1_START, TILE_MAP_1_END),
tileSet_0(memory, TILE_SET_0_START, true),
tileSet_1(memory, TILE_SET_1_START, false),
backgroundColourPaletteData(0xFF68),
spriteColourPaletteData(0xFF6A) {
    this->memory = memory;
    this->config = config;

    config->backgroundColourPalettes = backgroundColourPaletteData.palettes;
    config->spriteColourPalettes = spriteColourPaletteData.palettes;
    config->tileMap_0 = &tileMap_0.pixels;
    config->tileMap_1 = &tileMap_1.pixels;
    config->tileSet_0 = &tileSet_0;
    config->tileSet_1 = &tileSet_1;
}

static void drawBackgroundLine(Pixels* pixels, Memory* memory, Control* control, TileMap* tileMap,
    TileSet* tileSet, palette palette, uint8 line, uint16 scrollX, uint16 scrollY, bool isColour,
    ColourPaletteData* colourPaletteData) {
    if(!control->background) return;

    uint16 localY = Bytes::wrappingAdd_8(scrollY, line);
    uint16 tileIndexY = localY / TILE_SIZE;

    for(uint16 tileIndexX = 0; tileIndexX < TILE_COUNT; tileIndexX++) {
        tileMap->drawTile(tileIndexX, tileIndexY, palette, tileSet, isColour, colourPaletteData);
    }

    uint32* linePixels = tileMap->pixels.getLine(localY, scrollX, SCREEN_WIDTH);
    pixels->setLine(line, linePixels, 0, SCREEN_WIDTH);
}

static void drawWindowLine(Pixels* pixels, Memory* memory, Control* control, TileMap* tileMap_0, TileMap* tileMap_1,
        TileSet* tileSet, palette palette, uint8 line, bool isColour, ColourPaletteData* colourPaletteData) {
    if(!control->window) return;

    uint8 windowX = memory->coreMemory->get_8(WINDOW_X) - 7;
    uint8 windowY = memory->coreMemory->get_8(WINDOW_Y);

    if(line < windowY) return;

    uint8 localY = Bytes::wrappingSub_8(line, windowY);
    uint8 tileIndexY = localY / 8;
    TileMap* windowTileMap = !control->alternateWindowTileMap ? tileMap_0 : tileMap_1;

    for(uint8 tileIndexX = 0; tileIndexX < TILE_COUNT; tileIndexX++) {
        if(tileIndexX > FINAL_INDEX) continue;
        windowTileMap->drawTile(tileIndexX, tileIndexY, palette, tileSet, isColour, colourPaletteData);
    }

    uint32* linePixels = windowTileMap->pixels.getLine(localY, 0, SCREEN_WIDTH);
    pixels->setLine(line, linePixels, windowX, SCREEN_WIDTH - windowX);
}

static void drawSpriteLine(Pixels* pixels, Memory* memory, Control* control, uint8 line,
        TileSet* tileSet, uint16 scrollX, uint16 scrollY, palette backgroundPalette, bool isColour,
        ColourPaletteData* backgroundColourPaletteData, ColourPaletteData* spriteColourPaletteData, TileMap* tileMap) {
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
                    backgroundPalette, spritePalette_0, spritePalette_1, isColour, backgroundColourPaletteData,
                    spriteColourPaletteData, tileMap);
        }
    }
}

void Display::drawLine(Pixels *pixels, uint8 line, bool isColour, Control *control) {
    TileSet* tileSet = !control->alternateBackgroundTileSet ? &tileSet_0 : &tileSet_1;
    TileMap* tileMap = !control->alternateBackgroundTileMap ? &tileMap_0 : &tileMap_1;
    palette backgroundMonochromePalette = MonochromePalette::get(memory->get_8(BACKGROUND_PALETTE));
    uint16 scrollX = memory->coreMemory->get_8(SCROLL_X);
    uint16 scrollY = memory->coreMemory->get_8(SCROLL_Y);;

    drawBackgroundLine(pixels, memory, control, tileMap, tileSet, backgroundMonochromePalette, line, scrollX, scrollY, isColour, &backgroundColourPaletteData);
    drawWindowLine(pixels, memory, control, &tileMap_0, &tileMap_1, tileSet, backgroundMonochromePalette, line, isColour, &backgroundColourPaletteData);
    drawSpriteLine(pixels, memory, control, line, &tileSet_1, scrollX, scrollY, backgroundMonochromePalette, isColour, &backgroundColourPaletteData, &spriteColourPaletteData, tileMap);
}

uint8 Display::get_8(uint16 address) {
    if(address == 0xFF69)
        return backgroundColourPaletteData.get_8(address);

    if(address == 0xFF6A)
        return spriteColourPaletteData.get_8(address);

    return 0;
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

    if(address == 0xFF68 || address == 0xFF69) {
        backgroundColourPaletteData.set_8(address, value);
        tileMap_0.invalidateAllTiles();
        tileMap_1.invalidateAllTiles();
        return true;
    }

    if(address == 0xFF6A || address == 0xFF6B) {
        spriteColourPaletteData.set_8(address, value);
        tileMap_0.invalidateAllTiles();
        tileMap_1.invalidateAllTiles();
        return true;
    }

    return true;
}
