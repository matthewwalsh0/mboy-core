//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_INSTRUCTIONS_H
#define MY_APPLICATION_INSTRUCTIONS_H

#include <sys/types.h>
#include "CPU.h"
#include "MemoryHook.h"

struct instructionInfo {
    u_int8_t length;
    u_int8_t cyclesAction;
    u_int8_t cyclesNoAction;
    char debug[20];
};

class Instructions {
public:
    static instructionInfo getInfo(u_int8_t index, u_int8_t arg);
    static bool run(u_int8_t index, CPU* cpu, MemoryHook* memory, u_int8_t arg_8, u_int16_t arg_16);
    static void call(CPU* cpu, MemoryHook* memory, u_int16_t value);
};


#endif //MY_APPLICATION_INSTRUCTIONS_H
