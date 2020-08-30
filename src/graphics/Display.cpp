//
// Created by matthew on 06/07/2020.
//

#include "Display.h"
#include "MemoryMap.h"
#include "MonochromePalette.h"
#include "Bytes.h"
#include "GPU.h"
#include "Sprite.h"

const u_int8_t FINAL_INDEX = SCREEN_WIDTH / TILE_SIZE;

Display::Display(MemoryHook *memory, struct config* config) :
tileMap_0(memory, TILE_MAP_0_START, TILE_MAP_0_END, &config->disableTileMapCache),
tileMap_1(memory, TILE_MAP_1_START, TILE_MAP_1_END, &config->disableTileMapCache),
tileSet_0(memory, TILE_SET_0_START, true, &config->disableTileSetCache),
tileSet_1(memory, TILE_SET_1_START, false, &config->disableTileSetCache),
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

static void drawBackgroundLine(Pixels* pixels, MemoryHook* memory, Control* control, TileMap* tileMap,
    TileSet* tileSet, palette palette, u_int8_t line, u_int16_t scrollX, u_int16_t scrollY, bool isColour,
    ColourPaletteData* colourPaletteData, bool enable) {
    if(!enable) {
        pixels->clearLine(line, 0, SCREEN_WIDTH);
        return;
    }

    if(!control->background) return;

    u_int16_t localY = Bytes::wrappingAdd_8(scrollY, line);
    u_int16_t tileIndexY = localY / TILE_SIZE;

    for(u_int16_t tileIndexX = 0; tileIndexX < TILE_COUNT; tileIndexX++) {
        tileMap->drawTile(tileIndexX, tileIndexY, palette, tileSet, isColour, colourPaletteData);
    }

    u_int32_t* linePixels = tileMap->pixels.getLine(localY, scrollX, SCREEN_WIDTH);
    pixels->setLine(line, linePixels, 0, SCREEN_WIDTH);
    delete linePixels;
}

static void drawWindowLine(Pixels* pixels, MemoryHook* memory, Control* control, TileMap* tileMap_0, TileMap* tileMap_1,
        TileSet* tileSet, palette palette, u_int8_t line, bool isColour, ColourPaletteData* colourPaletteData, bool enable) {
    if(!control->window || !enable) return;

    u_int8_t windowX = memory->get_8(WINDOW_X) - 7;
    u_int8_t windowY = memory->get_8(WINDOW_Y);

    if(line < windowY) return;

    u_int8_t localY = Bytes::wrappingSub_8(line, windowY);
    u_int8_t tileIndexY = localY / 8;
    TileMap* windowTileMap = !control->alternateWindowTileMap ? tileMap_0 : tileMap_1;

    for(u_int8_t tileIndexX = 0; tileIndexX < TILE_COUNT; tileIndexX++) {
        if(tileIndexX > FINAL_INDEX) continue;
        windowTileMap->drawTile(tileIndexX, tileIndexY, palette, tileSet, isColour, colourPaletteData);
    }

    u_int8_t width = windowX > SCREEN_WIDTH ? SCREEN_WIDTH : SCREEN_WIDTH - windowX;
    u_int32_t* linePixels = windowTileMap->pixels.getLine(localY, 0, SCREEN_WIDTH);
    pixels->setLine(line, linePixels, windowX, width);
    delete linePixels;
}

static void drawSpriteLine(Pixels* pixels, MemoryHook* memory, Control* control, u_int8_t line,
        TileSet* tileSet, u_int16_t scrollX, u_int16_t scrollY, palette backgroundPalette, bool isColour,
        ColourPaletteData* backgroundColourPaletteData, ColourPaletteData* spriteColourPaletteData,
        TileMap* tileMap, bool enable, Sprite** spriteCache) {
    if(!control->sprites || !enable) return;

    palette spritePalette_0 = MonochromePalette::get(memory->get_8(SPRITE_PALETTE_0));
    palette spritePalette_1 = MonochromePalette::get(memory->get_8(SPRITE_PALETTE_1));

    for(int8_t i = 39; i >= 0; i--) {
        Sprite* sprite = spriteCache[i];

        if(sprite == nullptr) {
            u_int16_t spriteStart = SPRITE_INFO_START + (4 * i);
            sprite = new Sprite(memory, spriteStart, control->largeSprites);
            spriteCache[i] = sprite;
        }

        if(sprite->y == 0 && sprite->x == 0) continue;

        u_int16_t spriteYStart = sprite->y - 16;
        u_int16_t spriteYEnd = control->largeSprites ? spriteYStart + 16 : spriteYStart + 8;

        if(line >= spriteYStart && line < spriteYEnd) {
            u_int16_t localY = line - spriteYStart;
            sprite->drawLine(pixels, tileSet, scrollX, scrollY, localY,
                    backgroundPalette, spritePalette_0, spritePalette_1, isColour, backgroundColourPaletteData,
                    spriteColourPaletteData, tileMap);
        }
    }
}

void Display::clearSprite(u_int16_t address) {
    u_int16_t index = (address - SPRITE_INFO_START) / 4;
    spriteCache[index] = nullptr;
}

void Display::drawLine(Pixels *pixels, u_int8_t line, bool isColour, Control *control) {
    TileSet* tileSet = !control->alternateBackgroundTileSet ? &tileSet_0 : &tileSet_1;
    TileMap* tileMap = !control->alternateBackgroundTileMap ? &tileMap_0 : &tileMap_1;
    palette backgroundMonochromePalette = MonochromePalette::get(memory->get_8(BACKGROUND_PALETTE));
    u_int16_t scrollX = memory->get_8(SCROLL_X);
    u_int16_t scrollY = memory->get_8(SCROLL_Y);;

    drawBackgroundLine(pixels, memory, control, tileMap, tileSet, backgroundMonochromePalette, line, scrollX, scrollY, isColour, &backgroundColourPaletteData, config->background);
    drawWindowLine(pixels, memory, control, &tileMap_0, &tileMap_1, tileSet, backgroundMonochromePalette, line, isColour, &backgroundColourPaletteData, config->window);
    drawSpriteLine(pixels, memory, control, line, &tileSet_1, scrollX, scrollY, backgroundMonochromePalette, isColour, &backgroundColourPaletteData, &spriteColourPaletteData, tileMap, config->sprites, spriteCache);
}

u_int8_t Display::get_8(u_int16_t address) {
    if(address == 0xFF69)
        return backgroundColourPaletteData.get_8(address);

    if(address == 0xFF6A)
        return spriteColourPaletteData.get_8(address);

    return 0;
}

static void invalidateTile(TileMap* tileMap, u_int16_t address) {
    u_int16_t index = address - tileMap->start;
    int tileIndexY = index / TILE_COUNT;
    int tileIndexX = index % TILE_COUNT;
    tileMap->invalidateTile(tileIndexX, tileIndexY);
}

bool Display::set_8(u_int16_t address, u_int8_t value) {
    if(address >= TILE_SET_0_START && address < TILE_SET_0_END) {
        tileSet_0.clearCache();
        tileMap_0.invalidateAllTiles();
        tileMap_1.invalidateAllTiles();
        return true;
    }
    
    if(address >= TILE_SET_1_START && address < TILE_SET_1_END) {
        tileSet_1.clearCache();
        tileMap_0.invalidateAllTiles();
        tileMap_1.invalidateAllTiles();
        return true;
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
