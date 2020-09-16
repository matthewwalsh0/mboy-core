//
// Created by matthew on 06/07/2020.
//

#ifndef MY_APPLICATION_TILESET_H
#define MY_APPLICATION_TILESET_H

#include "Types.h"
#include "MemoryHook.h"
#include "Tile.h"

class TileSet {
private:
    u_int16_t start;
    bool isSigned;
    Tile* tileCache[1024 * 2];
    bool tileCacheSet[1024 * 2];
    MemoryHook* memory;
    bool* disableCache;
public:
    TileSet(MemoryHook* memory, u_int16_t start, bool isSigned, bool* disableCache);
    Tile* getTile(u_int8_t index, bool large, bool alternateBank, bool useCache);
    void clearCache();
};

#endif //MY_APPLICATION_TILESET_H
