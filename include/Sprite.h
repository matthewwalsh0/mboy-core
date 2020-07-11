//
// Created by matthew on 11/07/2020.
//

#ifndef MBOY_SPRITE_H
#define MBOY_SPRITE_H


#include "../include/Types.h"
#include "../include/Memory.h"
#include "../include/Tile.h"

class Sprite {
public:
    uint8 x;
    uint8 y;

    Sprite(Memory* memory, uint16 start, bool largeSprites);
    void drawLine(Pixels* pixels, TileSet* tileSet, uint16 scrollX, uint16 scrollY,
                  uint16 localY, palette backgroundPalette, palette palette_0, palette palette_1);
private:
    uint8 tileIndex;
    bool priority;
    bool yFlip;
    bool xFlip;
    bool alternatePalette;
    bool alternateBank;
    bool large;
    Memory* memory;
};


#endif //MBOY_SPRITE_H
