//
// Created by matthew on 06/07/2020.
//

#ifndef MY_APPLICATION_DISPLAY_H
#define MY_APPLICATION_DISPLAY_H

#include "TileMap.h"
#include "Control.h"
#include "ColourPaletteData.h"
#include "Sprite.h"

class Display : MemoryHook {
private:
    MemoryHook* memory;
    TileMap tileMap_0;
    TileMap tileMap_1;
    TileSet tileSet_0;
    TileSet tileSet_1;
    ColourPaletteData backgroundColourPaletteData;
    ColourPaletteData spriteColourPaletteData;
    struct config* config;
    Sprite* spriteCache[40];
public:
    Display(MemoryHook* memory, struct config* config);
    void drawLine(Pixels* pixels, uint8 line, bool isColour, Control* control);
    void clearSprite(uint16 address);

    uint8 get_8(uint16 address) override;
    bool set_8(uint16 address, uint8 value) override;
};


#endif //MY_APPLICATION_DISPLAY_H
