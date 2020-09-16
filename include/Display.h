//
// Created by matthew on 06/07/2020.
//

#ifndef MY_APPLICATION_DISPLAY_H
#define MY_APPLICATION_DISPLAY_H

#include "TileMap.h"
#include "Control.h"
#include "ColourPaletteData.h"
#include "Sprite.h"

class Display {
private:
    MemoryHook* memory;
    Config* config;
    Sprite* spriteCache[40];
public:
    TileMap tileMap_0;
    TileMap tileMap_1;
    TileSet tileSet_0;
    TileSet tileSet_1;
    ColourPaletteData backgroundColourPaletteData;
    ColourPaletteData spriteColourPaletteData;

    Display(MemoryHook* memory, Config* config);
    void drawLine(Pixels* pixels, u_int8_t line, bool isColour, Control* control);
    void clearSprite(u_int16_t address);
    void invalidateTile(TileMap* tileMap, u_int16_t address);
};


#endif //MY_APPLICATION_DISPLAY_H
