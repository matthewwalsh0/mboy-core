//
// Created by matthew on 06/07/2020.
//

#ifndef MY_APPLICATION_TILEMAP_H
#define MY_APPLICATION_TILEMAP_H


#include "Pixels.h"
#include "Memory.h"
#include "Tile.h"
#include "TileSet.h"

const uint8 TILE_COUNT = 32;

class TileMap {
private:
    Memory* memory;
    uint16 start;
    uint16 end;
public:
    Pixels pixels;

    TileMap(Memory* memory, uint16 start, uint16 end);
    uint16 getIndex(uint16 tileX, uint16 tileY);
    uint16 getAttributeIndex(uint16 tileX, uint16 tileY);
    void drawTile(uint16 tileIndexX, uint16 tileIndexY, palette palette, TileSet* tileSet);
};


#endif //MY_APPLICATION_TILEMAP_H
