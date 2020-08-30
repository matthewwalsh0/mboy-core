//
// Created by matthew on 06/07/2020.
//

#include "TileMap.h"

const uint16 WIDTH = TILE_COUNT * TILE_SIZE;
const uint16 HEIGHT = WIDTH;

TileMap::TileMap(MemoryHook *memory, uint16 start, uint16 end, bool* disableCache) : pixels(WIDTH, HEIGHT) {
    this->memory = memory;
    this->start = start;
    this->end = end;
    this->disableCache = disableCache;
}

uint16 TileMap::getIndex(uint16 tileX, uint16 tileY) {
    return memory->get_8(tileY * 32 + tileX + start, 0);
}

uint16 TileMap::getAttributeIndex(uint16 tileX, uint16 tileY) {
    return memory->get_8(tileY * 32 + tileX + start, 1);
}

void TileMap::drawTile(uint16 tileIndexX, uint16 tileIndexY, palette monochromePalette, TileSet *tileSet,
    bool isColour, ColourPaletteData* colourPaletteData) {
    uint16 index = tileIndexY * TILE_COUNT + tileIndexX;
    if(!*disableCache && !invalidTiles[index]) return;

    uint16 tileIndex = getIndex(tileIndexX, tileIndexY);
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
    uint16 targetX = tileIndexX * TILE_SIZE;

    for(uint8 y = 0; y < TILE_SIZE; y++) {
        uint16 targetY = tileIndexY * TILE_SIZE + y;
        tile->drawLine(&pixels, palette, y, targetX, targetY, flipX, flipY);
    }

    invalidTiles[index] = false;
}

void TileMap::invalidateTile(uint16 tileIndexX, uint16 tileIndexY) {
    uint16 index = tileIndexY * TILE_COUNT + tileIndexX;
    invalidTiles[index] = true;
}

void TileMap::invalidateAllTiles() {
    for(uint16 x = 0; x < TILE_COUNT; x++) {
        for(uint16 y = 0; y < TILE_COUNT; y++) {
            invalidateTile(x, y);
        }
    }
}

BackgroundAttributes TileMap::getBackgroundAttributes(uint8 tileX, uint8 tileY) {
    uint8 data = getAttributeIndex(tileX, tileY);
    return BackgroundAttributes(data);
}
