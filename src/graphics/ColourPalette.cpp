//
// Created by matthew on 28/07/2020.
//

#include "ColourPalette.h"
#include "Bytes.h"

static u_int32_t getColour(u_int8_t data1, u_int8_t data2) {
    u_int32_t total = Bytes::join_8(data2, data1);
    u_int8_t red = total & 0x1F;
    u_int8_t green = (total >> 5) & 0x1F;
    u_int8_t blue = (total >> 10) & 0x1F;
    u_int8_t newRed = (red * 255) / 31;
    u_int8_t newGreen = (green * 255) / 31;
    u_int8_t newBlue = (blue * 255) / 31;

    return Bytes::join_32(newBlue, newGreen, newRed) | 0xFF000000;
}

palette ColourPalette::fromData(u_int8_t *paletteData, u_int8_t index) {
    u_int32_t colour_0 = getColour(paletteData[index], paletteData[index + 1]);
    u_int32_t colour_1 = getColour(paletteData[index + 2], paletteData[index + 3]);
    u_int32_t colour_2 = getColour(paletteData[index + 4], paletteData[index + 5]);
    u_int32_t colour_3 = getColour(paletteData[index + 6], paletteData[index + 7]);

    palette colourPalette;
    colourPalette.isColour = true;
    colourPalette.colours[0] = colour_0;
    colourPalette.colours[1] = colour_1;
    colourPalette.colours[2] = colour_2;
    colourPalette.colours[3] = colour_3;

    return colourPalette;
}
