//
// Created by matthew on 04/07/2020.
//

#ifndef MY_APPLICATION_CPU_H
#define MY_APPLICATION_CPU_H

#include "Types.h"
#include "MemoryHook.h"
#include "LogFile.h"

enum Register {
    A,
    B,
    C,
    D,
    E,
    H,
    L,
    BC,
    DE,
    HL,
    AF
};

class CPU {

public:
    uint8 a;
    uint8 b;
    uint8 c;
    uint8 d;
    uint8 e;
    uint8 h;
    uint8 l;
    uint16 sp;
    uint16 pc;

    bool flag_z;
    bool flag_n;
    bool flag_h;
    bool flag_c;

    bool interruptsEnabled;
    bool halt;
    bool swapSpeed;
    uint8 currentSpeed;

    bool interruptEnableVerticalBlank = false;
    bool interruptEnableLcd = false;
    bool interruptEnableTimer = false;
    bool interruptEnableSerial = false;
    bool interruptEnableJoypad = false;

    bool interruptFlagsVerticalBlank = false;
    bool interruptFlagsLcd = false;
    bool interruptFlagsTimer = false;
    bool interruptFlagsSerial = false;
    bool interruptFlagsJoypad = false;

    LogFile logFile;

    CPU();
    uint8 get_8(Register cpuRegister);
    uint8 get_f();
    void set_f(uint8 value);
    uint16 get_16(Register cpuRegister);
    void set_8(Register cpuRegister, uint8 value);
    void set_16(Register cpuRegister, uint16 value);
    uint16 step(MemoryHook* memory, uint32 count, bool debug);
    uint8 getInterruptEnable();
    uint8 getInterruptFlags();
    void setInterruptEnable(uint8 value);
    void setInterruptFlags(uint8 value);
    void flagInterrupt(uint8 bit);
    uint8 get_8(uint16 address);
    bool set_8(uint16 address, uint8 value);

private:
    uint16 checkInterrupts(MemoryHook* memory);
};


#endif //MY_APPLICATION_CPU_H
