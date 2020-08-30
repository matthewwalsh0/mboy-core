//
// Created by matthew on 11/07/2020.
//

#ifndef MBOY_SPRITE_H
#define MBOY_SPRITE_H


#include <sys/types.h>
#include "MemoryHook.h"
#include "Tile.h"

class Sprite {
public:
    u_int8_t x;
    u_int8_t y;

    Sprite(MemoryHook* memory, u_int16_t start, bool largeSprites);
    void drawLine(Pixels* pixels, TileSet* tileSet, u_int16_t scrollX, u_int16_t scrollY,
                  u_int16_t localY, palette backgroundPalette, palette palette_0, palette palette_1,
                  bool isColour, ColourPaletteData* backgroundColourPaletteData, ColourPaletteData* spriteColourPaletteData, TileMap* tileMap);
private:
    u_int8_t tileIndex;
    bool priority;
    bool yFlip;
    bool xFlip;
    bool alternatePalette;
    bool alternateBank;
    u_int8_t colourPaletteIndex;
    bool large;
    MemoryHook* memory;
};


#endif //MBOY_SPRITE_H
