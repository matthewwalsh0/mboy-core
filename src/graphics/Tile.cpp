//
// Created by matthew on 06/07/2020.
//

#include "Tile.h"
#include "Bytes.h"

static void getColours(MemoryHook* memory, u_int16_t start, u_int32_t* colourIndexes, bool large, bool alternateBank) {
    u_int16_t y = 0;
    u_int16_t bytesEnd = large ? TILE_SIZE_LARGE * 2 : TILE_SIZE * 2;
    u_int8_t vramBank = alternateBank ? 1 : 0;

    for(u_int16_t index = 0; index < bytesEnd; index += 2) {
        u_int8_t byte_1 = memory->get_8(start + index, vramBank);
        u_int8_t byte_2 =  memory->get_8(start + index + 1, vramBank);
        u_int16_t x = 0;

        for(u_int8_t i = 0; i < TILE_SIZE; i++) {
            u_int8_t bit = TILE_SIZE - 1 - i;
            bool first = Bytes::getBit_8(byte_1, bit);
            bool second = Bytes::getBit_8(byte_2, bit);
            u_int16_t xy = y * TILE_SIZE + x;

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

Tile::Tile(MemoryHook *memory, u_int16_t start, bool large, bool alternateBank) {
    this->large = large;
    getColours(memory, start, colourIndexes, large, alternateBank);
}

void Tile::drawLine(Pixels *pixels, palette palette, u_int16_t localY, u_int16_t targetX, u_int16_t targetY,
                    bool flipX, bool flipY) {
    u_int16_t cacheIndex = palette.checksum * localY;
    bool cached = !palette.isColour && paletteCacheSet[cacheIndex];

    if(cached) {
        pixels->setLine(targetY, paletteCache + cacheIndex, targetX, TILE_SIZE);
        return;
    }

    u_int16_t tileY = flipY ? TILE_SIZE - 1 - localY : localY;
    u_int16_t yIndex = tileY * TILE_SIZE;
    u_int32_t* linePixels = paletteCache + cacheIndex;

    for(u_int8_t x = 0; x < TILE_SIZE; x++) {
        u_int16_t tileX = flipX ? TILE_SIZE - 1 - x : x;
        u_int8_t colourIndex = colourIndexes[yIndex + tileX];
        u_int32_t pixel = palette.colours[colourIndex];

        linePixels[x] = pixel;
    }

    pixels->setLine(targetY, linePixels, targetX, TILE_SIZE);
    paletteCacheSet[cacheIndex] = true;
}

void Tile::drawLineAdvanced(Pixels *pixels, palette palette, u_int16_t localY, u_int16_t targetX, u_int16_t targetY,
                            bool flipX, bool flipY, bool large, bool transparentColourZero, bool priority,
                            u_int16_t localX, u_int16_t targetWidth, u_int32_t priorityColour) {
    u_int8_t height = large ? TILE_SIZE_LARGE - 1 : TILE_SIZE - 1;

    for(u_int8_t x = localX; x < TILE_SIZE; x++) {
        u_int8_t tileX = flipX ? TILE_SIZE - 1 - x : x;
        u_int8_t tileY = flipY ? height - localY : localY;
        u_int8_t colourIndex = colourIndexes[tileY * 8 + tileX];

        if(transparentColourZero && colourIndex == 0) { continue; }

        u_int32_t pixel = palette.colours[colourIndex];
        u_int16_t finalX = Bytes::wrappingSub_8(Bytes::wrappingAdd_8(targetX, x), localX);

        if(finalX >= targetWidth) continue;

        u_int32_t targetPixel = pixels->get(finalX, targetY);

        if(!priority && targetPixel != priorityColour) continue;

        pixels->set(finalX, targetY, pixel);
    }
}
