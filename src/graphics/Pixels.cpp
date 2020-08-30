//
// Created by matthew on 05/07/2020.
//

#include "Pixels.h"
#include <cstring>

Pixels::Pixels(u_int16_t width, u_int16_t height) {
    this->width = width;
    this->height = height;
    data = new u_int32_t[width * height];
    createdData = true;

    for(u_int32_t i = 0; i < (width * height); i++) {
        data[i] = WHITE;
    }
}

Pixels::Pixels(u_int16_t width, u_int16_t height, u_int32_t* data) {
    this->width = width;
    this->height = height;
    this->data = data;
}

Pixels::~Pixels()
{
    if(createdData)
        delete data;
}

u_int32_t Pixels::get(u_int16_t x, u_int16_t y) {
    return data[getIndex(x, y)];
}

void Pixels::set(u_int16_t x, u_int16_t y, u_int32_t pixel) {
    data[getIndex(x, y)] = pixel;
}

void Pixels::setLine(u_int16_t y, u_int32_t *pixels, u_int16_t offset, u_int16_t width) {
    u_int32_t startIndex = y * this->width + offset;
    memcpy(data + startIndex, pixels, width * sizeof(u_int32_t));
}

void Pixels::clearLine(u_int16_t y, u_int16_t offset, u_int16_t width) {
    u_int32_t startIndex = y * width + offset;

    for(u_int16_t x = 0; x < width; x++) {
        data[startIndex++] = WHITE;
    }
}

u_int32_t* Pixels::getLine(u_int16_t y, u_int16_t offset, u_int16_t width) {
    u_int32_t* lineData = new u_int32_t[width];
    u_int32_t lineStart = y * this->width;
    u_int32_t sourceIndex = lineStart + offset;
    u_int32_t lastIndex = offset + width;

    if(this->width > lastIndex) {
        memcpy(lineData, data + sourceIndex, width * sizeof(u_int32_t));
    } else {
        u_int16_t firstWidth = this->width - offset;
        u_int16_t overflowWidth = lastIndex - this->width;
        memcpy(lineData, data + sourceIndex, firstWidth * sizeof(u_int32_t));
        memcpy(lineData + firstWidth, data + lineStart, overflowWidth * sizeof(u_int32_t));
    }

    return lineData;
}

u_int16_t Pixels::getIndex(u_int16_t x, u_int16_t y) {
    return y * width + x;
}

void Pixels::paste(u_int16_t x, u_int16_t y, Pixels* pixels) {
    for(u_int16_t y2 = 0; y2 < pixels->height; y2++) {
        u_int32_t* lineData = pixels->getLine(y2, 0, pixels->width);
        setLine(y + y2, lineData, x, pixels->width);
        delete lineData;
    }
}