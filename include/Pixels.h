//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_PIXELS_H
#define MY_APPLICATION_PIXELS_H

#include "Types.h"

const uint32 WHITE = 0xFFFFFFFF;

class Pixels {
private:
    uint16 getIndex(uint16 x, uint16 y);
    bool createdData = false;
public:
    uint16 width;
    uint16 height;
    uint32* data;

    Pixels(uint16 width, uint16 height);
    Pixels(uint16 width, uint16 height, uint32* data);
    ~Pixels();
    uint32 get(uint16 x, uint16 y);
    void set(uint16 x, uint16 y, uint32 pixel);
    void setLine(uint16 y, uint32* pixels, uint16 offset, uint16 width);
    void clearLine(uint16 y, uint16 offset, uint16 width);
    uint32* getLine(uint16 y, uint16 offset, uint16 width);
    void paste(uint16 x, uint16 y, Pixels* pixels);
};

#endif //MY_APPLICATION_PIXELS_H
