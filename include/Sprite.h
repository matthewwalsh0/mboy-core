//
// Created by matthew on 11/07/2020.
//

#ifndef MBOY_SPRITE_H
#define MBOY_SPRITE_H


#include "Types.h"
#include "MemoryHook.h"
#include "Tile.h"

class Sprite {
public:
    uint8 x;
    uint8 y;

    Sprite(MemoryHook* memory, uint16 start, bool largeSprites);
    void drawLine(Pixels* pixels, TileSet* tileSet, uint16 scrollX, uint16 scrollY,
                  uint16 localY, palette backgroundPalette, palette palette_0, palette palette_1,
                  bool isColour, ColourPaletteData* backgroundColourPaletteData, ColourPaletteData* spriteColourPaletteData, TileMap* tileMap);
private:
    uint8 tileIndex;
    bool priority;
    bool yFlip;
    bool xFlip;
    bool alternatePalette;
    bool alternateBank;
    uint8 colourPaletteIndex;
    bool large;
    MemoryHook* memory;
};


#endif //MBOY_SPRITE_H
