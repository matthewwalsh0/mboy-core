//
// Created by matthew on 06/07/2020.
//

#ifndef MY_APPLICATION_TILE_H
#define MY_APPLICATION_TILE_H

#include <sys/types.h>
#include "MemoryHook.h"
#include "Pixels.h"
#include "VRAM.h"

const u_int16_t TILE_SIZE = 8;
const u_int16_t TILE_SIZE_LARGE = 16;

struct palette {
    u_int32_t colours[4] = {0};
    bool isColour = false;
    u_int8_t checksum;
};

class Tile {
private:
    u_int32_t colourIndexes[TILE_SIZE * TILE_SIZE];
    bool large;
    u_int32_t paletteCache[256 * TILE_SIZE * TILE_SIZE];
    bool paletteCacheSet[256 * TILE_SIZE] = {[0 ... 256 * TILE_SIZE - 1] = false};
public:
    Tile(MemoryHook* memory, u_int16_t start, bool large, bool alternateBank);
    void drawLine(Pixels* pixels, palette palette, u_int16_t localY,
            u_int16_t targetX, u_int16_t targetY, bool flipX, bool flipY);
    void drawLineAdvanced(Pixels *pixels, palette palette, u_int16_t localY, u_int16_t targetX, u_int16_t targetY,
            bool flipX, bool flipY, bool large, bool transparentColourZero, bool priority,
            u_int16_t localX, u_int16_t targetWidth, u_int32_t priorityColour);
};

#endif //MY_APPLICATION_TILE_H
