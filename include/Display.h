//
// Created by matthew on 06/07/2020.
//

#ifndef MY_APPLICATION_DISPLAY_H
#define MY_APPLICATION_DISPLAY_H

#include "TileMap.h"
#include "Control.h"

class Display : MemoryHook {
private:
    Memory* memory;
    TileMap tileMap_0;
    TileMap tileMap_1;
    TileSet tileSet_0;
    TileSet tileSet_1;
public:
    Display(Memory* memory);
    void drawLine(Pixels* pixels, uint8 line, bool isColour, Control* control);
    uint8 get_8(uint16 address) override;
    bool set_8(uint16 address, uint8 value) override;
};


#endif //MY_APPLICATION_DISPLAY_H