//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_INSTRUCTIONS_H
#define MY_APPLICATION_INSTRUCTIONS_H

#include "Types.h"
#include "CPU.h"
#include "MemoryHook.h"

struct instructionInfo {
    uint8 length;
    uint8 cyclesAction;
    uint8 cyclesNoAction;
    char debug[20];
};

class Instructions {
public:
    static instructionInfo getInfo(uint8 index, uint8 arg);
    static bool run(uint8 index, CPU* cpu, MemoryHook* memory, uint8 arg_8, uint16 arg_16);
    static void call(CPU* cpu, MemoryHook* memory, uint16 value);
};


#endif //MY_APPLICATION_INSTRUCTIONS_H
