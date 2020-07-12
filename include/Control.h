//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_CONTROL_H
#define MY_APPLICATION_CONTROL_H

#include "Types.h"
#include "Memory.h"

class Control {
public:
    bool background;
    bool sprites;
    bool largeSprites;
    bool alternateBackgroundTileMap;
    bool alternateBackgroundTileSet;
    bool window;
    bool alternateWindowTileMap;
    bool display;

    Control(uint8 value);
    Control(Memory* memory);
};

#endif //MY_APPLICATION_CONTROL_H