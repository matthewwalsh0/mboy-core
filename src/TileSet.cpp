//
// Created by matthew on 06/07/2020.
//

#include "TileSet.h"
#include "Bytes.h"

TileSet::TileSet(uint16 start, bool isSigned) {
    this->start = start;
    this->isSigned = isSigned;
}

Tile* TileSet::getTile(Memory *memory, uint8 index, bool large, bool alternateBank) {
    uint16 actualIndex = isSigned ? Bytes::wrappingAdd_8(Bytes::toSigned_8(index), 128) : index;
    uint16 cacheIndex = ((alternateBank ? 1 : 0) * 1024) + actualIndex;
    bool tileCached = tileCacheSet[cacheIndex];

    if(tileCached) {
        Tile* cachedTile = tileCache[cacheIndex];
        return cachedTile;
    }

    uint16 tileStart = actualIndex * 16;
    Tile* tile = new Tile(memory, start + tileStart, large, alternateBank);
    tileCache[cacheIndex] = tile;
    tileCacheSet[cacheIndex] = true;

    return tile;
}

void TileSet::clearCache() {
    for(uint16 i = 0; i < 2048; i++) {
        bool isCached = tileCacheSet[i];

        if(isCached) {
            Tile* oldTile = tileCache[i];
            delete oldTile;
        }

        tileCacheSet[i] = false;
    }
}
