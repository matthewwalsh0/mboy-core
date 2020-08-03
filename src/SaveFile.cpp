//
// Created by matthew on 03/08/2020.
//

#include <fstream>
#include <iostream>
#include <filesystem>
#include "SaveFile.h"

SaveFile::SaveFile(std::string name) {
    this->name = name;
    this->fileName = std::filesystem::path(name).stem().string() + ".sav";

    std::ifstream existingFile (this->fileName, std::ios::binary | std::ios::ate);

    if(existingFile)
    {
        uint32 fileSize = existingFile.tellg();
        existingFile.seekg(0, std::ios::beg);
        existingFile.read((char*) data, fileSize);
        existingFile.close();
    }

    this->file.open(this->fileName);
}

uint8 SaveFile::get_8(uint32 address) {
    return data[address];
}

bool SaveFile::set_8(uint32 address, uint8 value) {
    const char data[1] = {(char) value};
    this->data[address] = value;
    this->file.seekp(address, std::ios::beg);
    this->file.write(data, 1);
    this->file.flush();
    return true;
}
