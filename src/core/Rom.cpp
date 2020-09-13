#include "Rom.h"

#include <fstream>

#include "MemoryMap.h"
#include "MBC1.h"
#include "MBC3.h"
#include "MBC5.h"

const u_int16_t ADDRESS_TITLE_START = 0x0134;
const u_int16_t ROM_SIZE = 0x8000;
const u_int32_t MAX_ROM_SIZE = 1024 * 1024 * 8;

static Controller* getController(u_int8_t* rom) {
    u_int8_t value = rom[ADDRESS_TYPE];

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

static std::string readName(u_int8_t* rom) {
    char name[30];
    strcpy(name, (const char*) rom + ADDRESS_TITLE_START);
    return std::string(name);
}

Rom::Rom(std::string filename, Memory* memory) {
    std::ifstream file (filename, std::ios::binary | std::ios::ate);

    if(!file)
    {
        throw std::invalid_argument(
            "Cannot read file.\nFile: " + filename + "\nReason: " + strerror(errno));
    }

    rom = new u_int8_t[MAX_ROM_SIZE];
    for(u_int32_t i = 0; i < MAX_ROM_SIZE; i++) {
        rom[i] = 0;
    }

    u_int32_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    file.read((char*) rom, fileSize);

    name = readName(this->rom);
    controller = getController(rom);
    isColour = rom[ADDRESS_COLOUR_FLAG] == 0x80 || rom[ADDRESS_COLOUR_FLAG] == 0xC0;

    ram = (Ram*) new SaveFile(filename);

    auto getter = [this]MEMORY_GETTER_LAMBDA {
        return get_8(address, bank);
    };

    auto setter = [this]MEMORY_SETTER_LAMBDA {
        return set_8(address, value);
    };

    memory->registerGetter(0, 0x7FFF, getter);
    memory->registerGetter(0xA000, 0xBFFF, getter);

    memory->registerSetter(0, 0x7FFF, setter);
    memory->registerSetter(0xA000, 0xBFFF, setter);
}

u_int8_t Rom::get_8(u_int16_t address, u_int8_t bank) {
    if(controller != nullptr) {
        int16_t controllerValue = this->controller->get_8(address, rom, ram);
        if(controllerValue != -1) return controllerValue;
    }

    if(address < ROM_SIZE) {
        return this->rom[address];
    }

    return 0;
}

bool Rom::set_8(u_int16_t address, u_int8_t value) {
    if(controller != nullptr) {
        bool set = this->controller->set_8(address, value, rom, ram);
        if(set) return true;
    }

    return true;
}
