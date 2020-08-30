//
// Created by matthew on 04/07/2020.
//

#ifndef MY_APPLICATION_ROM_H
#define MY_APPLICATION_ROM_H

#include <sys/types.h>
#include "MemoryHook.h"
#include "SaveFile.h"
#include <string>
#include "Ram.h"

class Controller {
public:
    virtual int16_t get_8(u_int16_t address, u_int8_t* rom, Ram* ram) { return 0; };
    virtual bool set_8(u_int16_t address, u_int8_t value, u_int8_t* rom, Ram* ram) { return false; };
};

class Rom {

private:
    u_int8_t* rom;
    Ram* ram;
    Controller* controller;

    std::string readName(u_int8_t* rom);

public:
    bool isColour = false;
    std::string name;

    Rom(std::string filename);
    u_int8_t get_8(u_int16_t address);
    bool set_8(u_int16_t address, u_int8_t value);
};

#endif //MY_APPLICATION_ROM_H
