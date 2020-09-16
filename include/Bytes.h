//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_BYTES_H
#define MY_APPLICATION_BYTES_H

#include "Types.h"

class Bytes {
public:
    static u_int8_t setBit_8(u_int8_t value, u_int8_t index);
    static u_int8_t getBit_8(u_int8_t value, u_int8_t index);
    static u_int8_t clearBit_8(u_int8_t value, u_int8_t index);
    static u_int8_t join_4(u_int8_t upper, u_int8_t lower);
    static u_int16_t join_8(u_int8_t upper, u_int8_t lower);
    static u_int32_t join_32(u_int8_t first, u_int8_t second, u_int8_t third);
    static u_int8_t split_8_upper(u_int8_t value);
    static u_int8_t split_8_lower(u_int8_t value);
    static u_int8_t split_16_upper(u_int16_t value);
    static u_int8_t split_16_lower(u_int16_t value);
    static bool isHalfCarrySub_8(u_int8_t value_1, u_int8_t value_2);
    static bool isHalfCarrySub_8_three(u_int8_t value_1, u_int8_t value_2, u_int8_t value_3);
    static bool isHalfCarryAdd_8(u_int8_t value_1, u_int8_t value_2);
    static bool isHalfCarryAdd_8_three(u_int8_t value_1, u_int8_t value_2, u_int8_t value_3);
    static bool isHalfCarryAdd_16(u_int16_t value_1, u_int16_t value_2);
    static bool isCarrySub_8_three(u_int8_t value_1, u_int8_t value_2, u_int8_t value_3);
    static bool isCarryAdd_8(u_int8_t value_1, u_int8_t value_2);
    static bool isCarryAdd_8_three(u_int8_t value_1, u_int8_t value_2, u_int8_t value_3);
    static bool isCarryAdd_16(u_int16_t value_1, u_int16_t value_2);
    static u_int8_t wrappingAdd_8(u_int8_t value, u_int8_t add);
    static u_int16_t wrappingAdd_16(u_int16_t value, u_int16_t add);
    static u_int8_t wrappingSub_8(u_int8_t value, u_int8_t sub);
    static u_int16_t wrappingSub_16(u_int16_t value, u_int16_t sub);
    static u_int8_t rotateRight_8(u_int8_t value, u_int8_t n);
    static u_int8_t rotateLeft_8(u_int8_t value, u_int8_t n);
    static int8_t toSigned_8(u_int8_t value);
};

#endif //MY_APPLICATION_BYTES_H
