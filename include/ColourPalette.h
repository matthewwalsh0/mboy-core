//
// Created by matthew on 28/07/2020.
//

#ifndef MBOY_ANDROID_COLOURPALETTE_H
#define MBOY_ANDROID_COLOURPALETTE_H


#include "Types.h"
#include "Tile.h"

class ColourPalette {
public:
    static palette fromData(u_int8_t* data, u_int8_t index);
};

#endif //MBOY_ANDROID_COLOURPALETTE_H
