//
// Created by matthew on 28/07/2020.
//

#ifndef MBOY_ANDROID_COLOURPALETTEDATA_H
#define MBOY_ANDROID_COLOURPALETTEDATA_H

#include "Types.h"
#include "Tile.h"

class ColourPaletteData {
private:
    uint8 data[64] = {0};
    uint8 index = 0;
    bool autoIncrement = false;
    uint16 address;

public:
    palette palettes[8];
    ColourPaletteData(uint16 address);
    palette getPalette(uint8 index);
    uint8 get_8(uint16 address);
    bool set_8(uint16 address, uint8 value);
};

#endif //MBOY_ANDROID_COLOURPALETTEDATA_H
