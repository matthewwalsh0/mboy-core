//
// Created by matthew on 04/07/2020.
//

#ifndef MY_APPLICATION_ROM_H
#define MY_APPLICATION_ROM_H

#include "Types.h"
#include <string>

class Rom {

private:
    uint8 rom[0xFFFF] = {0};

    std::string readName(uint8* rom);

public:
    bool isColour = false;
    std::string name;

    Rom(std::string filename);
    uint8 get_8(uint16 address);
    bool set_8(uint16 address, uint8 value);
};

#endif //MY_APPLICATION_ROM_H
