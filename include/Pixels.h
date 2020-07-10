//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_PIXELS_H
#define MY_APPLICATION_PIXELS_H

#include "Types.h"

const uint32 WHITE = 0x00FFFFFF;

class Pixels {
private:
    uint16 width;
    uint16 height;

    uint16 getIndex(uint16 x, uint16 y);
public:
    uint32* data;

    Pixels(uint16 width, uint16 height);
    uint32 get(uint16 x, uint16 y);
    void set(uint16 x, uint16 y, uint32 pixel);
    void setLine(uint16 y, uint32* pixels, uint16 offset, uint16 width);
    void clearLine(uint16 y, uint16 offset, uint16 width);
    uint32* getLine(uint16 y, uint16 offset, uint16 width);
};

#endif //MY_APPLICATION_PIXELS_H
