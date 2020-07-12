//
// Created by matthew on 05/07/2020.
//

#include "Pixels.h"
#include <cstring>

uint32 Pixels::get(uint16 x, uint16 y) {
    return data[getIndex(x, y)];
}

void Pixels::set(uint16 x, uint16 y, uint32 pixel) {
    data[getIndex(x, y)] = pixel;
}

void Pixels::setLine(uint16 y, uint32 *pixels, uint16 offset, uint16 width) {
    uint16 startIndex = y * this->width + offset;
    memcpy(data + startIndex, pixels, width * sizeof(uint32));
}

void Pixels::clearLine(uint16 y, uint16 offset, uint16 width) {
    uint16 startIndex = y * width + offset;

    for(uint16 x = 0; x < width; x++) {
        data[startIndex++] = WHITE;
    }
}

uint32 *Pixels::getLine(uint16 y, uint16 offset, uint16 width) {
    uint16 lineStart = y * this->width;
    uint16 sourceIndex = lineStart + offset;
   
    return data + sourceIndex;
}

uint16 Pixels::getIndex(uint16 x, uint16 y) {
    return y * width + x;
}

Pixels::Pixels(uint16 width, uint16 height) {
    this->width = width;
    this->height = height;
    data = new uint32[width * height];
}
