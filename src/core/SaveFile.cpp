//
// Created by matthew on 03/08/2020.
//

#include <fstream>
#include <iostream>
#include <regex>
#include "SaveFile.h"

SaveFile::SaveFile(std::string name) {
    this->name = name;
    this->fileName = name;

    this->fileName = std::regex_replace(this->fileName, std::regex("\\.gbc"), "");
    this->fileName = std::regex_replace(this->fileName, std::regex("\\.gb"), "");
    this->fileName += ".sav";

    std::ifstream existingFile (this->fileName, std::ios::binary | std::ios::ate);

    if(existingFile)
    {
        uint32 fileSize = existingFile.tellg();
        existingFile.seekg(0, std::ios::beg);
        existingFile.read((char*) data, fileSize);
        existingFile.close();
    }

    this->file.open(this->fileName);
    
    if(!this->file) {
        throw std::invalid_argument("Cannot write file.\nFile: " + this->fileName + "\nReason: " + strerror(errno));
    }
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
