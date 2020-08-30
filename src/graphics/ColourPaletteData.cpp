//
// Created by matthew on 28/07/2020.
//

#include "ColourPaletteData.h"
#include "Bytes.h"
#include "ColourPalette.h"

ColourPaletteData::ColourPaletteData(uint16 address) {
    this->address = address;
}

palette ColourPaletteData::getPalette(uint8 index) {
    return palettes[index];
}

uint8 ColourPaletteData::get_8(uint16 address) {
    return data[index];
}

bool ColourPaletteData::set_8(uint16 address, uint8 value) {
    uint16 relativeAddress = address - this->address;

    switch(relativeAddress) {
        case 0:
            index = value & 0x3F;
            autoIncrement = Bytes::getBit_8(value, 7);
            return true;
        case 1:
            data[index] = value;
            uint8 paletteIndex = index / 8;
            palettes[paletteIndex] = ColourPalette::fromData(data, paletteIndex * 8);

            if(autoIncrement) {
                index = (index + 1) & 0x3F;
            }

            return true;
    }

    return true;
}

