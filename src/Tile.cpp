//
// Created by matthew on 06/07/2020.
//

#include "Tile.h"
#include "Bytes.h"

static void getColours(Memory* memory, uint16 start, uint32* colourIndexes, bool large, bool alternateBank) {
    uint16 y = 0;
    uint16 bytesEnd = large ? TILE_SIZE_LARGE * 2 : TILE_SIZE * 2;

    for(uint16 index = 0; index < bytesEnd; index += 2) {
        uint8 byte_1 = memory->coreMemory->get_8(start + index);
        uint8 byte_2 =  memory->coreMemory->get_8(start + index + 1);
        uint16 x = 0;

        for(uint8 i = 0; i < TILE_SIZE; i++) {
            uint8 bit = TILE_SIZE - 1 - i;
            bool first = Bytes::getBit_8(byte_1, bit);
            bool second = Bytes::getBit_8(byte_2, bit);
            uint16 xy = y * TILE_SIZE + x;

            if(!first && !second) {
                colourIndexes[xy] = 0;
            } else if(first && !second) {
                colourIndexes[xy] = 1;
            } else if(!first && second) {
                colourIndexes[xy] = 2;
            } else if(first && second) {
                colourIndexes[xy] = 3;
            }

            x += 1;
        }

        y += 1;
    }
}

Tile::Tile(Memory *memory, uint16 start, bool large, bool alternateBank) {
    this->large = large;
    getColours(memory, start, colourIndexes, false, false);
}

void Tile::drawLine(Pixels *pixels, palette palette, uint16 localY, uint16 targetX, uint16 targetY,
                    bool flipX, bool flipY) {
    uint16 cacheIndex = palette.value * localY;
    bool cached = paletteCacheSet[cacheIndex];

    if(cached) {
        pixels->setLine(targetY, paletteCache + cacheIndex, targetX, TILE_SIZE);
        return;
    }

    uint16 tileY = flipY ? TILE_SIZE - 1 - localY : localY;
    uint16 yIndex = tileY * TILE_SIZE;
    uint32* linePixels = paletteCache + cacheIndex;

    for(uint8 x = 0; x < TILE_SIZE; x++) {
        uint16 tileX = flipX ? TILE_SIZE - 1 - x : x;
        uint8 colourIndex = colourIndexes[yIndex + tileX];
        uint32 pixel = palette.colours[colourIndex];

        linePixels[x] = pixel;
    }

    pixels->setLine(targetY, linePixels, targetX, TILE_SIZE);
    paletteCacheSet[cacheIndex] = true;
}

void Tile::drawLineAdvanced(Pixels *pixels, palette palette, uint16 localY, uint16 targetX, uint16 targetY,
                            bool flipX, bool flipY, bool large, bool transparentColourZero, bool priority,
                            uint16 localX, uint16 targetWidth, uint32 priorityColour) {
    uint8 height = large ? TILE_SIZE_LARGE - 1 : TILE_SIZE - 1;

    for(uint8 x = localX; x < TILE_SIZE; x++) {
        uint8 tileX = flipX ? TILE_SIZE - 1 - x : x;
        uint8 tileY = flipY ? height - localY : localY;
        uint8 colourIndex = colourIndexes[tileY * 8 + tileX];

        if(transparentColourZero && colourIndex == 0) { continue; }

        uint32 pixel = palette.colours[colourIndex];
        uint16 finalX = Bytes::wrappingSub_8(Bytes::wrappingAdd_8(targetX, x), localX);

        if(finalX >= targetWidth) continue;

        uint32 targetPixel = pixels->get(finalX, targetY);

        if(!priority && targetPixel != priorityColour) continue;

        pixels->set(finalX, targetY, pixel);
    }
}
