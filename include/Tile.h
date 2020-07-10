//
// Created by matthew on 06/07/2020.
//

#ifndef MY_APPLICATION_TILE_H
#define MY_APPLICATION_TILE_H

#include "Types.h"
#include "Memory.h"
#include "Pixels.h"

const uint16 TILE_SIZE = 8;
const uint16 TILE_SIZE_LARGE = 16;

struct palette {
    uint32 colours[4] = {0};
};

class Tile {
private:
    uint32 colourIndexes[TILE_SIZE * TILE_SIZE];
    bool large;
public:
    Tile(Memory* memory, uint16 start, bool large, bool alternateBank);
    void drawLine(Pixels* pixels, palette palette, uint16 localY,
            uint16 targetX, uint16 targetY, bool flipX, bool flipY);
};

#endif //MY_APPLICATION_TILE_H
