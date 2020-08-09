//
// Created by matthew on 06/07/2020.
//

#ifndef MY_APPLICATION_TILEMAP_H
#define MY_APPLICATION_TILEMAP_H


#include "Pixels.h"
#include "MemoryHook.h"
#include "Tile.h"
#include "TileSet.h"
#include "BackgroundAttributes.h"
#include "ColourPaletteData.h"
#include "Config.h"

const uint8 TILE_COUNT = 32;

class TileMap {
private:
    MemoryHook* memory;
    uint16 end;
    bool invalidTiles[TILE_COUNT * TILE_COUNT] = {[0 ... TILE_COUNT * TILE_COUNT - 1] = true};
    bool* disableCache;
public:
    uint16 start;
    Pixels pixels;

    TileMap(MemoryHook* memory, uint16 start, uint16 end, bool* disableCache);
    uint16 getIndex(uint16 tileX, uint16 tileY);
    uint16 getAttributeIndex(uint16 tileX, uint16 tileY);
    BackgroundAttributes getBackgroundAttributes(uint8 tileX, uint8 tileY);
    void drawTile(uint16 tileIndexX, uint16 tileIndexY, palette palette, TileSet* tileSet, bool isColour, ColourPaletteData* colourPaletteData);
    void invalidateTile(uint16 tileIndexX, uint16 tileIndexY);
    void invalidateAllTiles();
};


#endif //MY_APPLICATION_TILEMAP_H
