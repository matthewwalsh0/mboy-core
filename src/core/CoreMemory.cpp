#include "CoreMemory.h"

#include "Bytes.h"
#include "MemoryMap.h"

u_int8_t CoreMemory::get_8(u_int16_t address) {
    return data[address];
}

bool CoreMemory::set_8(u_int16_t address, u_int8_t value) {
    data[address] = value;
    return true;
}
