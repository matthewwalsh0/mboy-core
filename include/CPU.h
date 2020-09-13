#ifndef MY_APPLICATION_CPU_H
#define MY_APPLICATION_CPU_H

#include <sys/types.h>

#include "MemoryHook.h"
#include "LogFile.h"
#include "Memory.h"

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
    u_int8_t a;
    u_int8_t b;
    u_int8_t c;
    u_int8_t d;
    u_int8_t e;
    u_int8_t h;
    u_int8_t l;
    u_int16_t sp;
    u_int16_t pc;

    bool flag_z;
    bool flag_n;
    bool flag_h;
    bool flag_c;

    bool interruptsEnabled;
    bool halt;
    bool swapSpeed;
    u_int8_t currentSpeed;

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

    CPU(Memory* memory);
    u_int8_t get_8(Register cpuRegister);
    u_int8_t get_f();
    void set_f(u_int8_t value);
    u_int16_t get_16(Register cpuRegister);
    void set_8(Register cpuRegister, u_int8_t value);
    void set_16(Register cpuRegister, u_int16_t value);
    u_int16_t step(MemoryHook* memory, u_int32_t count, bool debug);
    u_int8_t getInterruptEnable();
    u_int8_t getInterruptFlags();
    void setInterruptEnable(u_int8_t value);
    void setInterruptFlags(u_int8_t value);
    void flagInterrupt(u_int8_t bit);

private:
    u_int16_t checkInterrupts(MemoryHook* memory);
};


#endif //MY_APPLICATION_CPU_H
