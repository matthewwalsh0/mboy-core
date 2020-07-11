//
// Created by matthew on 06/07/2020.
//

#include "TileMap.h"

const uint16 WIDTH = TILE_COUNT * TILE_SIZE;
const uint16 HEIGHT = WIDTH;

TileMap::TileMap(Memory *memory, uint16 start, uint16 end) : pixels(WIDTH, HEIGHT) {
    this->memory = memory;
    this->start = start;
    this->end = end;
}

uint16 TileMap::getIndex(uint16 tileX, uint16 tileY) {
    return memory->coreMemory->get_8(tileY * 32 + tileX + start);
}

uint16 TileMap::getAttributeIndex(uint16 tileX, uint16 tileY) {
    return memory->coreMemory->get_8(tileY * 32 + tileX + start);
}

void TileMap::drawTile(uint16 tileIndexX, uint16 tileIndexY, palette palette, TileSet *tileSet) {
    uint16 index = tileIndexY * TILE_COUNT + tileIndexX;
    if(!invalidTiles[index]) return;

    uint16 tileIndex = getIndex(tileIndexX, tileIndexY);
    Tile* tile = tileSet->getTile(memory, tileIndex, false, false);
    uint16 targetX = tileIndexX * TILE_SIZE;

    for(uint8 y = 0; y < TILE_SIZE; y++) {
        uint16 targetY = tileIndexY * TILE_SIZE + y;
        tile->drawLine(&pixels, palette, y, targetX, targetY, false, false);
    }
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
