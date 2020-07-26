//
// Created by matthew on 04/07/2020.
//

#ifndef MY_APPLICATION_ROM_H
#define MY_APPLICATION_ROM_H

#include "Types.h"
#include "MemoryHook.h"
#include <string>

class Controller {
public:
    virtual int16 get_8(uint16 address, uint8* rom, uint8* ram) { return 0; };
    virtual bool set_8(uint16 address, uint8 value, uint8* rom, uint8* ram) { return false; };
};

class Rom {

private:
    uint8* rom;
    uint8 ram[128 * 1024] = {0};
    Controller* controller;

    std::string readName(uint8* rom);

public:
    bool isColour = false;
    std::string name;

    Rom(std::string filename);
    uint8 get_8(uint16 address);
    bool set_8(uint16 address, uint8 value);
};

#endif //MY_APPLICATION_ROM_H
