//
// Created by matthew on 05/07/2020.
//

#ifndef MY_APPLICATION_BYTES_H
#define MY_APPLICATION_BYTES_H

#include "Types.h"

class Bytes {
public:
    static uint8 setBit_8(uint8 value, uint8 index);
    static uint8 getBit_8(uint8 value, uint8 index);
    static uint8 clearBit_8(uint8 value, uint8 index);
    static uint8 join_4(uint8 upper, uint8 lower);
    static uint16 join_8(uint8 upper, uint8 lower);
    static uint32 join_32(uint8 first, uint8 second, uint8 third);
    static uint8 split_8_upper(uint8 value);
    static uint8 split_8_lower(uint8 value);
    static uint8 split_16_upper(uint16 value);
    static uint8 split_16_lower(uint16 value);
    static bool isHalfCarrySub_8(uint8 value_1, uint8 value_2);
    static bool isHalfCarrySub_8_three(uint8 value_1, uint8 value_2, uint8 value_3);
    static bool isHalfCarryAdd_8(uint8 value_1, uint8 value_2);
    static bool isHalfCarryAdd_8_three(uint8 value_1, uint8 value_2, uint8 value_3);
    static bool isHalfCarryAdd_16(uint16 value_1, uint16 value_2);
    static bool isCarrySub_8_three(uint8 value_1, uint8 value_2, uint8 value_3);
    static bool isCarryAdd_8(uint8 value_1, uint8 value_2);
    static bool isCarryAdd_8_three(uint8 value_1, uint8 value_2, uint8 value_3);
    static bool isCarryAdd_16(uint16 value_1, uint16 value_2);
    static uint8 wrappingAdd_8(uint8 value, uint8 add);
    static uint16 wrappingAdd_16(uint16 value, uint16 add);
    static uint8 wrappingSub_8(uint8 value, uint8 sub);
    static uint16 wrappingSub_16(uint16 value, uint16 sub);
    static uint8 rotateRight_8(uint8 value, uint8 n);
    static uint8 rotateLeft_8(uint8 value, uint8 n);
    static int8 toSigned_8(uint8 value);
};

#endif //MY_APPLICATION_BYTES_H
