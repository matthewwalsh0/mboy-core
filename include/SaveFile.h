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
    u_int8_t data[128 * 1024] = {0};
public:
    SaveFile(std::string name);
    u_int8_t get_8(u_int32_t address);
    bool set_8(u_int32_t address, u_int8_t value);
};

#endif //MY_APPLICATION_SAVEFILE_H
