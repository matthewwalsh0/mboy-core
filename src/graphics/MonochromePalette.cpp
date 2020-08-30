//
// Created by matthew on 06/07/2020.
//

#include "MonochromePalette.h"
#include <sys/types.h>
#include "Bytes.h"

const u_int32_t PALETTE_WHITE = 0xFFD0F8E0;
const u_int32_t LIGHT_GREY = 0xFF70C088;
const u_int32_t DARK_GREY = 0xFF566834;
const u_int32_t BLACK = 0xFF201808;

static u_int32_t getColour(bool first, bool second) {
    if(!first && !second) return PALETTE_WHITE;
    if(first && !second) return LIGHT_GREY;
    if(!first && second) return DARK_GREY;
    return BLACK;
}

palette MonochromePalette::get(u_int8_t value) {
    palette palette;

    palette.checksum = value;
    palette.colours[0] = getColour(Bytes::getBit_8(value, 0), Bytes::getBit_8(value, 1));
    palette.colours[1] = getColour(Bytes::getBit_8(value, 2), Bytes::getBit_8(value, 3));
    palette.colours[2] = getColour(Bytes::getBit_8(value, 4), Bytes::getBit_8(value, 5));
    palette.colours[3] = getColour(Bytes::getBit_8(value, 6), Bytes::getBit_8(value, 7));

    return palette;
}
