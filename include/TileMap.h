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

const u_int8_t TILE_COUNT = 32;

class TileMap {
private:
    MemoryHook* memory;
    u_int16_t end;
    bool invalidTiles[TILE_COUNT * TILE_COUNT] = {[0 ... TILE_COUNT * TILE_COUNT - 1] = true};
    bool* disableCache;
public:
    u_int16_t start;
    Pixels pixels;

    TileMap(MemoryHook* memory, u_int16_t start, u_int16_t end, bool* disableCache);
    u_int16_t getIndex(u_int16_t tileX, u_int16_t tileY);
    u_int16_t getAttributeIndex(u_int16_t tileX, u_int16_t tileY);
    BackgroundAttributes getBackgroundAttributes(u_int8_t tileX, u_int8_t tileY);
    void drawTile(u_int16_t tileIndexX, u_int16_t tileIndexY, palette palette, TileSet* tileSet, bool isColour, ColourPaletteData* colourPaletteData);
    void invalidateTile(u_int16_t tileIndexX, u_int16_t tileIndexY);
    void invalidateAllTiles();
};


#endif //MY_APPLICATION_TILEMAP_H
