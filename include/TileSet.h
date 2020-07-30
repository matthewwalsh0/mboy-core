//
// Created by matthew on 06/07/2020.
//

#ifndef MY_APPLICATION_TILESET_H
#define MY_APPLICATION_TILESET_H

#include "Types.h"
#include "Memory.h"
#include "Tile.h"

class TileSet : MemoryHook {
private:
    uint16 start;
    bool isSigned;
    Tile* tileCache[1024 * 2];
    bool tileCacheSet[1024 * 2] = {[0 ... 2047] = false};
public:
    TileSet(uint16 start, bool isSigned);
    Tile* getTile(Memory* memory, uint8 index, bool large, bool alternateBank);
    void clearCache();
};

#endif //MY_APPLICATION_TILESET_H
