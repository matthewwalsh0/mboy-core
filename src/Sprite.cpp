//
// Created by matthew on 11/07/2020.
//

#include <TileSet.h>
#include <GPU.h>
#include "Sprite.h"
#include "Bytes.h"

Sprite::Sprite(Memory *memory, uint16 start, bool largeSprites) {
    y = memory->coreMemory->get_8(start);
    x = memory->coreMemory->get_8(start + 1);
    tileIndex = !largeSprites ? memory->coreMemory->get_8(start + 2) :
            Bytes::clearBit_8(memory->coreMemory->get_8(start + 2), 0);
    priority = !Bytes::getBit_8(memory->coreMemory->get_8(start + 3), 7);
    yFlip = Bytes::getBit_8(memory->coreMemory->get_8(start + 3), 6);
    xFlip = Bytes::getBit_8(memory->coreMemory->get_8(start + 3), 5);
    alternatePalette = Bytes::getBit_8(memory->coreMemory->get_8(start + 3), 4);
    colourPaletteIndex = memory->coreMemory->get_8(start + 3) & 0x7;
    alternateBank = Bytes::getBit_8(memory->coreMemory->get_8(start + 3), 3);
    large = largeSprites;
    this->memory = memory;
}

void Sprite::drawLine(Pixels* pixels, TileSet* tileSet, uint16 scrollX, uint16 scrollY,
        uint16 localY, palette backgroundPalette, palette palette_0, palette palette_1,
        bool isColour, ColourPaletteData* backgroundColourPaletteData, ColourPaletteData* spriteColourPaletteData,
        TileMap* tileMap) {
    Tile* tile = tileSet->getTile(tileIndex, large, alternateBank, true);

    uint32 priorityColour;
        palette currentPalette;
        bool backgroundPriority = false;

        if(!isColour) {
                priorityColour = backgroundPalette.colours[0];
                currentPalette = alternatePalette ? palette_1 : palette_0;
        } else {
                uint8 tileIndexX = Bytes::wrappingAdd_8(scrollX, x - 8) / 8;
                uint8 tileIndexY = Bytes::wrappingAdd_8(scrollY, y - 16 + localY) / 8;
                BackgroundAttributes attributes = tileMap->getBackgroundAttributes(tileIndexX, tileIndexY);
                priorityColour = backgroundColourPaletteData->getPalette(attributes.paletteNumber).colours[0];
                currentPalette = spriteColourPaletteData->getPalette(colourPaletteIndex);
                backgroundPriority = attributes.priority;
        }

        bool currentPriority = !backgroundPriority && this->priority;

    tile->drawLineAdvanced(pixels, currentPalette, localY, x - 8, y - 16 + localY, xFlip, yFlip,
            large, true, currentPriority, 0, SCREEN_WIDTH, priorityColour);
}
