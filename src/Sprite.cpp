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
    large = largeSprites;
    this->memory = memory;
}

void Sprite::drawLine(Pixels* pixels, TileSet* tileSet, uint16 scrollX, uint16 scrollY,
        uint16 localY, palette backgroundPalette, palette palette_0, palette palette_1) {
    Tile* tile = tileSet->getTile(memory, tileIndex, large, false);
    palette palette = alternatePalette ? palette_1 : palette_0;
    uint32 priorityColour = backgroundPalette.colours[0];

    tile->drawLineAdvanced(pixels, palette, localY, x - 8, y - 16 + localY, xFlip, yFlip,
            large, true, priority, 0, SCREEN_WIDTH, priorityColour);
}
