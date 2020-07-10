//
// Created by matthew on 04/07/2020.
//

#include "Rom.h"
#include <fstream>

const uint16 ADDRESS_TITLE_START = 0x0134;
const uint16 ROM_SIZE = 0x8000;

Rom::Rom(std::string filename) {
    std::ifstream file (filename, std::ios::binary);
    file.read((char*) &this->rom, ROM_SIZE);
    this->name = readName(this->rom);
}

uint8 Rom::get_8(uint16 address) {
    if(address < ROM_SIZE) {
        return this->rom[address];
    }

    throw std::invalid_argument("Attempted to read from invalid ROM address.");
}

bool Rom::set_8(uint16 address, uint8 value) {
    return false;
}

std::string Rom::readName(uint8* rom) {
    char name[15];
    strcpy(name, (const char*) rom + ADDRESS_TITLE_START);
    return std::string(name);
}
