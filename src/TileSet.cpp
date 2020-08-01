//
// Created by matthew on 06/07/2020.
//

#include "TileSet.h"
#include "Bytes.h"

TileSet::TileSet(Memory* memory, uint16 start, bool isSigned) {
    this->memory = memory;
    this->start = start;
    this->isSigned = isSigned;
}

Tile* TileSet::getTile(uint8 index, bool large, bool alternateBank, bool useCache) {
    uint16 actualIndex = isSigned ? Bytes::wrappingAdd_8(Bytes::toSigned_8(index), 128) : index;
    uint16 cacheIndex = ((alternateBank ? 1 : 0) * 1024) + actualIndex;
    bool tileCached = tileCacheSet[cacheIndex];

    if(useCache && tileCached) {
        Tile* cachedTile = tileCache[cacheIndex];
        return cachedTile;
    }

    uint16 tileStart = actualIndex * 16;
    Tile* tile = new Tile(memory, start + tileStart, large, alternateBank);

    if(useCache) {
        tileCache[cacheIndex] = tile;
        tileCacheSet[cacheIndex] = true;
    }

    return tile;
}

void TileSet::clearCache() {
    for(uint16 i = 0; i < 2048; i++) {
        bool isCached = tileCacheSet[i];

        if(isCached) {
            Tile* oldTile = tileCache[i];
            if(oldTile != nullptr) {
                delete oldTile;
            }
        }

        tileCacheSet[i] = false;
    }
}
