//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_PIXELS_H
#define MY_APPLICATION_PIXELS_H

#include <sys/types.h>

const u_int32_t WHITE = 0xFFFFFFFF;

class Pixels {
private:
    u_int16_t getIndex(u_int16_t x, u_int16_t y);
    bool createdData = false;
public:
    u_int16_t width;
    u_int16_t height;
    u_int32_t* data;

    Pixels(u_int16_t width, u_int16_t height);
    Pixels(u_int16_t width, u_int16_t height, u_int32_t* data);
    ~Pixels();
    u_int32_t get(u_int16_t x, u_int16_t y);
    void set(u_int16_t x, u_int16_t y, u_int32_t pixel);
    void setLine(u_int16_t y, u_int32_t* pixels, u_int16_t offset, u_int16_t width);
    void clearLine(u_int16_t y, u_int16_t offset, u_int16_t width);
    u_int32_t* getLine(u_int16_t y, u_int16_t offset, u_int16_t width);
    void paste(u_int16_t x, u_int16_t y, Pixels* pixels);
};

#endif //MY_APPLICATION_PIXELS_H
