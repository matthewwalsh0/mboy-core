#include "SaveFile.h"

#include <fstream>
#include <iostream>
#include <regex>

#include "Log.h"

SaveFile::SaveFile(std::string name) {
    this->name = name;
    this->fileName = name;

    this->fileName = std::regex_replace(this->fileName, std::regex("\\.gbc"), "");
    this->fileName = std::regex_replace(this->fileName, std::regex("\\.gb"), "");
    this->fileName += ".sav";

    std::ifstream existingFile (this->fileName, std::ios::binary | std::ios::ate);

    if(existingFile)
    {
        u_int32_t fileSize = existingFile.tellg();
        existingFile.seekg(0, std::ios::beg);
        existingFile.read((char*) data, fileSize);
        existingFile.close();
    }

    this->file.open(this->fileName);
    
    if(!this->file) {
        throw std::invalid_argument("Cannot write file.\nFile: " + this->fileName + "\nReason: " + strerror(errno));
    }
}

u_int8_t SaveFile::get_8(u_int32_t address) {
    return data[address];
}

bool SaveFile::set_8(u_int32_t address, u_int8_t value) {
    MBOY_INFO("Writing to save file - {0} - 0x{1:X} = 0x{2:X}", this->fileName, address, value);

    const char data[1] = {(char) value};
    this->data[address] = value;
    this->file.seekp(address, std::ios::beg);
    this->file.write(data, 1);
    this->file.flush();
    return true;
}
