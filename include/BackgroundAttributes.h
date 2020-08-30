//
// Created by matthew on 28/07/2020.
//

#ifndef MBOY_ANDROID_BACKGROUNDATTRIBUTES_H
#define MBOY_ANDROID_BACKGROUNDATTRIBUTES_H


#include <sys/types.h>

class BackgroundAttributes {
public:
    u_int8_t paletteNumber;
    bool alternateBank;
    bool priority;
    bool flipX;
    bool flipY;

    BackgroundAttributes(u_int8_t data);
};


#endif //MBOY_ANDROID_BACKGROUNDATTRIBUTES_H
