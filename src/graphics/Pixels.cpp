//
// Created by matthew on 05/07/2020.
//

#include "Pixels.h"
#include <cstring>

Pixels::Pixels(uint16 width, uint16 height) {
    this->width = width;
    this->height = height;
    data = new uint32[width * height];
    createdData = true;

    for(uint32 i = 0; i < (width * height); i++) {
        data[i] = WHITE;
    }
}

Pixels::Pixels(uint16 width, uint16 height, uint32* data) {
    this->width = width;
    this->height = height;
    this->data = data;
}

Pixels::~Pixels()
{
    if(createdData)
        delete data;
}

uint32 Pixels::get(uint16 x, uint16 y) {
    return data[getIndex(x, y)];
}

void Pixels::set(uint16 x, uint16 y, uint32 pixel) {
    data[getIndex(x, y)] = pixel;
}

void Pixels::setLine(uint16 y, uint32 *pixels, uint16 offset, uint16 width) {
    uint32 startIndex = y * this->width + offset;
    memcpy(data + startIndex, pixels, width * sizeof(uint32));
}

void Pixels::clearLine(uint16 y, uint16 offset, uint16 width) {
    uint32 startIndex = y * width + offset;

    for(uint16 x = 0; x < width; x++) {
        data[startIndex++] = WHITE;
    }
}

uint32* Pixels::getLine(uint16 y, uint16 offset, uint16 width) {
    uint32* lineData = new uint32[width];
    uint32 lineStart = y * this->width;
    uint32 sourceIndex = lineStart + offset;
    uint32 lastIndex = offset + width;

    if(this->width > lastIndex) {
        memcpy(lineData, data + sourceIndex, width * sizeof(uint32));
    } else {
        uint16 firstWidth = this->width - offset;
        uint16 overflowWidth = lastIndex - this->width;
        memcpy(lineData, data + sourceIndex, firstWidth * sizeof(uint32));
        memcpy(lineData + firstWidth, data + lineStart, overflowWidth * sizeof(uint32));
    }

    return lineData;
}

uint16 Pixels::getIndex(uint16 x, uint16 y) {
    return y * width + x;
}

void Pixels::paste(uint16 x, uint16 y, Pixels* pixels) {
    for(uint16 y2 = 0; y2 < pixels->height; y2++) {
        uint32* lineData = pixels->getLine(y2, 0, pixels->width);
        setLine(y + y2, lineData, x, pixels->width);
        delete lineData;
    }
}