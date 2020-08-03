//
// Created by matthew on 03/08/2020.
//

#ifndef MY_APPLICATION_SAVEFILE_H
#define MY_APPLICATION_SAVEFILE_H

#include "Types.h"
#include "Ram.h"
#include <string>
#include <fstream>

class SaveFile : Ram {
private:
    std::string name;
    std::string fileName;
    std::ofstream file;
    uint8 data[128 * 1024] = {0};
public:
    SaveFile(std::string name);
    uint8 get_8(uint32 address);
    bool set_8(uint32 address, uint8 value);
};

#endif //MY_APPLICATION_SAVEFILE_H
