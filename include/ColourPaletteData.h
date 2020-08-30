//
// Created by matthew on 28/07/2020.
//

#ifndef MBOY_ANDROID_COLOURPALETTEDATA_H
#define MBOY_ANDROID_COLOURPALETTEDATA_H

#include <sys/types.h>
#include "Tile.h"

class ColourPaletteData {
private:
    u_int8_t data[64] = {0};
    u_int8_t index = 0;
    bool autoIncrement = false;
    u_int16_t address;

public:
    palette palettes[8];
    ColourPaletteData(u_int16_t address);
    palette getPalette(u_int8_t index);
    u_int8_t get_8(u_int16_t address);
    bool set_8(u_int16_t address, u_int8_t value);
};

#endif //MBOY_ANDROID_COLOURPALETTEDATA_H
