//
// Created by matthew on 11/07/2020.
//

#include "TileSet.h"
#include "GPU.h"
#include "Sprite.h"
#include "Bytes.h"

Sprite::Sprite(MemoryHook *memory, u_int16_t start, bool largeSprites) {
    y = memory->get_8(start);
    x = memory->get_8(start + 1);
    tileIndex = !largeSprites ? memory->get_8(start + 2) :
            Bytes::clearBit_8(memory->get_8(start + 2), 0);
    priority = !Bytes::getBit_8(memory->get_8(start + 3), 7);
    yFlip = Bytes::getBit_8(memory->get_8(start + 3), 6);
    xFlip = Bytes::getBit_8(memory->get_8(start + 3), 5);
    alternatePalette = Bytes::getBit_8(memory->get_8(start + 3), 4);
    colourPaletteIndex = memory->get_8(start + 3) & 0x7;
    alternateBank = Bytes::getBit_8(memory->get_8(start + 3), 3);
    large = largeSprites;
    this->memory = memory;
}

void Sprite::drawLine(Pixels* pixels, TileSet* tileSet, u_int16_t scrollX, u_int16_t scrollY,
        u_int16_t localY, palette backgroundPalette, palette palette_0, palette palette_1,
        bool isColour, ColourPaletteData* backgroundColourPaletteData, ColourPaletteData* spriteColourPaletteData,
        TileMap* tileMap) {
    Tile* tile = tileSet->getTile(tileIndex, large, alternateBank, true);

    u_int32_t priorityColour;
        palette currentPalette;
        bool backgroundPriority = false;

        if(!isColour) {
                priorityColour = backgroundPalette.colours[0];
                currentPalette = alternatePalette ? palette_1 : palette_0;
        } else {
                u_int8_t tileIndexX = Bytes::wrappingAdd_8(scrollX, x - 8) / 8;
                u_int8_t tileIndexY = Bytes::wrappingAdd_8(scrollY, y - 16 + localY) / 8;
                BackgroundAttributes attributes = tileMap->getBackgroundAttributes(tileIndexX, tileIndexY);
                priorityColour = backgroundColourPaletteData->getPalette(attributes.paletteNumber).colours[0];
                currentPalette = spriteColourPaletteData->getPalette(colourPaletteIndex);
                backgroundPriority = attributes.priority;
        }

        bool currentPriority = !backgroundPriority && this->priority;

    tile->drawLineAdvanced(pixels, currentPalette, localY, x - 8, y - 16 + localY, xFlip, yFlip,
            large, true, currentPriority, 0, SCREEN_WIDTH, priorityColour);
}
