//
// Created by matthew on 26/07/2020.
//

#ifndef MY_APPLICATION_CONFIG_H
#define MY_APPLICATION_CONFIG_H

#include "Tile.h"

struct config {
    bool turbo = false;
    palette* backgroundColourPalettes;
    palette* spriteColourPalettes;
    Pixels* tileMap_0;
    Pixels* tileMap_1;
    TileSet* tileSet_0;
    TileSet* tileSet_1;
};

#endif //MY_APPLICATION_CONFIG_H
