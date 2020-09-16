//
// Created by matthew on 06/07/2020.
//

#include "TileSet.h"

#include <algorithm>

#include "Bytes.h"

TileSet::TileSet(MemoryHook* memory, u_int16_t start, bool isSigned, bool* disableCache) {
    this->memory = memory;
    this->start = start;
    this->isSigned = isSigned;
    this->disableCache = disableCache;
    std::fill_n(tileCacheSet, 2048, false);
}

Tile* TileSet::getTile(u_int8_t index, bool large, bool alternateBank, bool useCache) {
    u_int16_t actualIndex = isSigned ? Bytes::wrappingAdd_8(Bytes::toSigned_8(index), 128) : index;
    u_int16_t cacheIndex = ((alternateBank ? 1 : 0) * 1024) + actualIndex;
    bool tileCached = tileCacheSet[cacheIndex];

    if(!*disableCache && useCache && tileCached) {
        Tile* cachedTile = tileCache[cacheIndex];
        return cachedTile;
    }

    u_int16_t tileStart = actualIndex * 16;
    Tile* tile = new Tile(memory, start + tileStart, large, alternateBank);

    if(useCache) {
        tileCache[cacheIndex] = tile;
        tileCacheSet[cacheIndex] = true;
    }

    return tile;
}

void TileSet::clearCache() {
    for(u_int16_t i = 0; i < 2048; i++) {
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
