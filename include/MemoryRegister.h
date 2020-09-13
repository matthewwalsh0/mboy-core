#ifndef MY_APPLICATION_MEMORYREGISTER_H
#define MY_APPLICATION_MEMORYREGISTER_H

#include <sys/types.h>
#include <functional>

#include "MemoryHook.h"

#define MEMORY_GETTER std::function<u_int8_t(u_int16_t, u_int8_t)>
#define MEMORY_SETTER std::function<bool(u_int16_t, u_int8_t)>
#define MEMORY_FLAGGER std::function<void(u_int8_t)>
#define MEMORY_GETTER_LAMBDA (u_int16_t address, u_int8_t bank) -> u_int8_t
#define MEMORY_SETTER_LAMBDA (u_int16_t address, u_int8_t value) -> bool
#define MEMORY_FLAGGER_LAMBDA (u_int8_t bit)

class MemoryRegister {
public:
    virtual void registerGetter(u_int16_t address, MEMORY_GETTER getter) = 0;
    virtual void registerGetter(u_int16_t start, u_int16_t end, MEMORY_GETTER getter) = 0;
    virtual void registerSetter(u_int16_t address, MEMORY_SETTER setter, bool override = true) = 0;
    virtual void registerSetter(u_int16_t start, u_int16_t end, MEMORY_SETTER setter, bool override = true) = 0;
    virtual void registerFlagger(MEMORY_FLAGGER flagger) = 0;
};

#endif
