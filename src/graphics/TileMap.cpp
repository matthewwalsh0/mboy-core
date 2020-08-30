//
// Created by matthew on 06/07/2020.
//

#include "TileMap.h"

const u_int16_t WIDTH = TILE_COUNT * TILE_SIZE;
const u_int16_t HEIGHT = WIDTH;

TileMap::TileMap(MemoryHook *memory, u_int16_t start, u_int16_t end, bool* disableCache) : pixels(WIDTH, HEIGHT) {
    this->memory = memory;
    this->start = start;
    this->end = end;
    this->disableCache = disableCache;
}

u_int16_t TileMap::getIndex(u_int16_t tileX, u_int16_t tileY) {
    return memory->get_8(tileY * 32 + tileX + start, 0);
}

u_int16_t TileMap::getAttributeIndex(u_int16_t tileX, u_int16_t tileY) {
    return memory->get_8(tileY * 32 + tileX + start, 1);
}

void TileMap::drawTile(u_int16_t tileIndexX, u_int16_t tileIndexY, palette monochromePalette, TileSet *tileSet,
    bool isColour, ColourPaletteData* colourPaletteData) {
    u_int16_t index = tileIndexY * TILE_COUNT + tileIndexX;
    if(!*disableCache && !invalidTiles[index]) return;

    u_int16_t tileIndex = getIndex(tileIndexX, tileIndexY);
    bool flipX = false;
    bool flipY = false;
    bool alternateBank = false;
    palette palette = monochromePalette;

    if(isColour) {
        BackgroundAttributes tileAttributes = getBackgroundAttributes(tileIndexX, tileIndexY);
        flipX = tileAttributes.flipX;
        flipY = tileAttributes.flipY;
        alternateBank = tileAttributes.alternateBank;
        palette = colourPaletteData->getPalette(tileAttributes.paletteNumber);
    }

    Tile* tile = tileSet->getTile(tileIndex, false, alternateBank, true);
    u_int16_t targetX = tileIndexX * TILE_SIZE;

    for(u_int8_t y = 0; y < TILE_SIZE; y++) {
        u_int16_t targetY = tileIndexY * TILE_SIZE + y;
        tile->drawLine(&pixels, palette, y, targetX, targetY, flipX, flipY);
    }

    invalidTiles[index] = false;
}

void TileMap::invalidateTile(u_int16_t tileIndexX, u_int16_t tileIndexY) {
    u_int16_t index = tileIndexY * TILE_COUNT + tileIndexX;
    invalidTiles[index] = true;
}

void TileMap::invalidateAllTiles() {
    for(u_int16_t x = 0; x < TILE_COUNT; x++) {
        for(u_int16_t y = 0; y < TILE_COUNT; y++) {
            invalidateTile(x, y);
        }
    }
}

BackgroundAttributes TileMap::getBackgroundAttributes(u_int8_t tileX, u_int8_t tileY) {
    u_int8_t data = getAttributeIndex(tileX, tileY);
    return BackgroundAttributes(data);
}
