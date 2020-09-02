#ifndef MY_APPLICATION_MEMORYREGISTER_H
#define MY_APPLICATION_MEMORYREGISTER_H

#include <sys/types.h>
#include "MemoryHook.h"

class MemoryRegister {
public:
    virtual void registerGetter(u_int16_t address, MemoryHook* getter) {};
    virtual void registerGetter(u_int16_t start, u_int16_t end, MemoryHook* getter) {};
    virtual void registerSetter(u_int16_t address, MemoryHook* setter, bool override = true) {};
    virtual void registerSetter(u_int16_t start, u_int16_t end, MemoryHook* setter, bool override = true) {};
};

#endif
