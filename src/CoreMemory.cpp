//
// Created by matthew on 05/07/2020.
//

#include "CoreMemory.h"
#include "Bytes.h"
#include "MemoryMap.h"

CoreMemory::CoreMemory() {

    set_8(0xFF10, 0x80);
    set_8(0xFF11, 0xBF);
    set_8(0xFF12, 0xF3);
    set_8(0xFF14, 0xBF);
    set_8(0xFF16, 0x3F);
    set_8(0xFF19, 0xBF);
    set_8(0xFF1A, 0x7F);
    set_8(0xFF1B, 0xFF);
    set_8(0xFF1C, 0x9F);
    set_8(0xFF1E, 0xBF);
    set_8(0xFF20, 0xFF);
    set_8(0xFF23, 0xBF);
    set_8(0xFF24, 0x77);
    set_8(0xFF25, 0xF3);
    set_8(0xFF26, 0xF1);
    set_8(0xFF47, 0xFC);
    set_8(0xFF48, 0xFF);
    set_8(0xFF48, 0xFF);
}

uint8 CoreMemory::get_8(uint16 address) {
    return data[address];
}

void CoreMemory::set_8(uint16 address, uint8 value) {
    data[address] = value;
}
