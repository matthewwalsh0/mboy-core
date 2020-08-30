//
// Created by matthew on 28/07/2020.
//

#include "ColourPalette.h"
#include "Bytes.h"

static uint32 getColour(uint8 data1, uint8 data2) {
    uint32 total = Bytes::join_8(data2, data1);
    uint8 red = total & 0x1F;
    uint8 green = (total >> 5) & 0x1F;
    uint8 blue = (total >> 10) & 0x1F;
    uint8 newRed = (red * 255) / 31;
    uint8 newGreen = (green * 255) / 31;
    uint8 newBlue = (blue * 255) / 31;

    return Bytes::join_32(newBlue, newGreen, newRed) | 0xFF000000;
}

palette ColourPalette::fromData(uint8 *paletteData, uint8 index) {
    uint32 colour_0 = getColour(paletteData[index], paletteData[index + 1]);
    uint32 colour_1 = getColour(paletteData[index + 2], paletteData[index + 3]);
    uint32 colour_2 = getColour(paletteData[index + 4], paletteData[index + 5]);
    uint32 colour_3 = getColour(paletteData[index + 6], paletteData[index + 7]);

    palette colourPalette;
    colourPalette.isColour = true;
    colourPalette.colours[0] = colour_0;
    colourPalette.colours[1] = colour_1;
    colourPalette.colours[2] = colour_2;
    colourPalette.colours[3] = colour_3;

    return colourPalette;
}
