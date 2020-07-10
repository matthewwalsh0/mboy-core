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
    for(uint8 x = 0; x < TILE_SIZE; x++) {
        uint16 tileX = flipX ? TILE_SIZE - 1 - x : x;
        uint16 tileY = flipY ? TILE_SIZE - 1 - localY : localY;
        uint8 colourIndex = colourIndexes[tileY * TILE_SIZE + tileX];
        uint32 pixel = palette.colours[colourIndex];
        uint16 finalX = targetX + x;

        pixels->set(finalX, targetY, pixel);
    }
}
