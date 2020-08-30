//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_CONTROL_H
#define MY_APPLICATION_CONTROL_H

#include <sys/types.h>
#include "MemoryHook.h"

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

    Control(u_int8_t value);
    Control(MemoryHook* memory);
};

#endif //MY_APPLICATION_CONTROL_H
