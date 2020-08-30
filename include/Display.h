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
    void drawLine(Pixels* pixels, u_int8_t line, bool isColour, Control* control);
    void clearSprite(u_int16_t address);

    u_int8_t get_8(u_int16_t address) override;
    bool set_8(u_int16_t address, u_int8_t value) override;
};


#endif //MY_APPLICATION_DISPLAY_H
