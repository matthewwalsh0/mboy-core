//
// Created by matthew on 04/07/2020.
//

#include "Rom.h"
#include <fstream>
#include <MemoryMap.h>
#include "MBC1.h"
#include "MBC3.h"
#include "MBC5.h"

const uint16 ADDRESS_TITLE_START = 0x0134;
const uint16 ROM_SIZE = 0x8000;
const uint32 MAX_ROM_SIZE = 1024 * 1024 * 8;

static Controller* getController(uint8* rom) {
    uint8 value = rom[ADDRESS_TYPE];

    if(value == 0x0) return nullptr;
    if(value == 0x1 || value == 0x3) {
        MBC1* controller = new MBC1();
        return (Controller*) controller;
    }
    if(value == 0x10 || value == 0x13) {
        MBC3* controller = new MBC3();
        return (Controller*) controller;
    }
    if(value >= 0x19 && value <= 0x1E) {
        MBC5* controller = new MBC5();
        return (Controller*) controller;
    }

    throw std::invalid_argument("Unsupported controller type.");
}

Rom::Rom(std::string filename) {
    std::ifstream file (filename, std::ios::binary | std::ios::ate);

    if(!file)
    {
        throw std::invalid_argument(
                "Cannot read file.\nFile: " + filename + "\nReason: " + strerror(errno));
    }

    rom = new uint8[MAX_ROM_SIZE];
    for(uint32 i = 0; i < MAX_ROM_SIZE; i++) {
        rom[i] = 0;
    }

    uint32 fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    file.read((char*) rom, fileSize);

    name = readName(this->rom);
    controller = getController(rom);
    isColour = rom[ADDRESS_COLOUR_FLAG] == 0x80 || rom[ADDRESS_COLOUR_FLAG] == 0xC0;

    ram = (Ram*) new SaveFile(filename);
}

uint8 Rom::get_8(uint16 address) {
    if(controller != nullptr) {
        int16 controllerValue = this->controller->get_8(address, rom, ram);
        if(controllerValue != -1) return controllerValue;
    }

    if(address < ROM_SIZE) {
        return this->rom[address];
    }

    return 0;
}

bool Rom::set_8(uint16 address, uint8 value) {
    if(controller != nullptr) {
        bool set = this->controller->set_8(address, value, rom, ram);
        if(set) return true;
    }

    return false;
}

std::string Rom::readName(uint8* rom) {
    char name[30];
    strcpy(name, (const char*) rom + ADDRESS_TITLE_START);
    return std::string(name);
}
