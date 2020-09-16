//
// Created by matthew on 26/07/2020.
//

#ifndef MY_APPLICATION_CONFIG_H
#define MY_APPLICATION_CONFIG_H

#include "Tile.h"
#include "TileSet.h"

struct Config {
    bool background = true;
    bool window = true;
    bool sprites = true;
    bool audio = true;
    bool square1 = true;
    bool square2 = true;
    bool wave = true;
    bool noise = true;
    bool turbo = false;
    bool disableTileMapCache = false;
    bool disableTileSetCache = false;
    palette* backgroundColourPalettes;
    palette* spriteColourPalettes;
    Pixels* tileMap_0;
    Pixels* tileMap_1;
    TileSet* tileSet_0;
    TileSet* tileSet_1;
};

#endif //MY_APPLICATION_CONFIG_H
