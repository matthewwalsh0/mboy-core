//
// Created by matthew on 28/07/2020.
//

#ifndef MBOY_ANDROID_BACKGROUNDATTRIBUTES_H
#define MBOY_ANDROID_BACKGROUNDATTRIBUTES_H


#include "Types.h"

class BackgroundAttributes {
public:
    uint8 paletteNumber;
    bool alternateBank;
    bool priority;
    bool flipX;
    bool flipY;

    BackgroundAttributes(uint8 data);
};


#endif //MBOY_ANDROID_BACKGROUNDATTRIBUTES_H
