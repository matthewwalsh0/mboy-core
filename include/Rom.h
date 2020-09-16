#ifndef MY_APPLICATION_ROM_H
#define MY_APPLICATION_ROM_H

#include "Types.h"
#include <string>

#include "MemoryHook.h"
#include "SaveFile.h"
#include "Ram.h"
#include "Memory.h"

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

    u_int8_t get_8(u_int16_t address, u_int8_t bank);
    bool set_8(u_int16_t address, u_int8_t value);
public:
    bool isColour = false;
    std::string name;

    Rom(std::string filename, Memory* memory);
};

#endif //MY_APPLICATION_ROM_H
