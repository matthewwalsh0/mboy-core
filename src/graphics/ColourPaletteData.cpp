//
// Created by matthew on 28/07/2020.
//

#include "ColourPaletteData.h"
#include "Bytes.h"
#include "ColourPalette.h"

ColourPaletteData::ColourPaletteData(u_int16_t address) {
    this->address = address;
}

palette ColourPaletteData::getPalette(u_int8_t index) {
    return palettes[index];
}

u_int8_t ColourPaletteData::get_8(u_int16_t address) {
    return data[index];
}

bool ColourPaletteData::set_8(u_int16_t address, u_int8_t value) {
    u_int16_t relativeAddress = address - this->address;

    switch(relativeAddress) {
        case 0:
            index = value & 0x3F;
            autoIncrement = Bytes::getBit_8(value, 7);
            return true;
        case 1:
            data[index] = value;
            u_int8_t paletteIndex = index / 8;
            palettes[paletteIndex] = ColourPalette::fromData(data, paletteIndex * 8);

            if(autoIncrement) {
                index = (index + 1) & 0x3F;
            }

            return true;
    }

    return true;
}

