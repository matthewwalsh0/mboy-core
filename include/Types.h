#ifndef TYPES_H
#define TYPES_H

#ifdef _WIN32

#include <stdint.h>

typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;

#else

#include <sys/types.h>

#endif

#endif
