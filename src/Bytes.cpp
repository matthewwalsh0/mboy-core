//
// Created by matthew on 05/07/2020.
//

#include "Bytes.h"

uint8 Bytes::setBit_8(uint8 value, uint8 index) {
    return value | (1 << index);
}

uint8 Bytes::getBit_8(uint8 value, uint8 index) {
    return (value & (1 << index)) != 0;
}

uint16 Bytes::join_8(uint8 upper, uint8 lower) {
    return (upper << 8) | lower;
}

uint8 Bytes::split_16_upper(uint16 value) {
    return value >> 8;
}

uint8 Bytes::split_16_lower(uint16 value) {
    return value & 0x00FF;
}

uint8 Bytes::clearBit_8(uint8 value, uint8 index) {
    return value & ~(1 << index);
}

uint8 Bytes::join_4(uint8 upper, uint8 lower) {
    return upper << 4 | lower;
}

uint32 Bytes::join_32(uint8 first, uint8 second, uint8 third) {
    return ((first << 16) | (second << 8)) | third;
}

uint8 Bytes::split_8_upper(uint8 value) {
    return value >> 4;
}

uint8 Bytes::split_8_lower(uint8 value) {
    return value & 0x0F;
}

bool Bytes::isHalfCarrySub_8(uint8 value_1, uint8 value_2) {
    int8 result = (value_1 & 0xF) - (value_2 & 0xF);
    return result < 0;
}

bool Bytes::isHalfCarrySub_8_three(uint8 value_1, uint8 value_2, uint8 value_3) {
    int16 result = (value_1 & 0xF) - (value_2 & 0xF) - (value_3 & 0xF);
    return result < 0;
}

bool Bytes::isHalfCarryAdd_8(uint8 value_1, uint8 value_2) {
    return (((value_1 & 0xF) + (value_2 & 0xF)) & 0x10) == 0x10;
}

bool Bytes::isHalfCarryAdd_8_three(uint8 value_1, uint8 value_2, uint8 value_3) {
    return (((value_1 & 0xF) + (value_2 & 0xF) + (value_3 & 0xF)) & 0x10) == 0x10;
}

bool Bytes::isHalfCarryAdd_16(uint16 value_1, uint16 value_2) {
    uint16 value_1_nibble_3 = value_1 & 0xFFF;
    uint16 value_2_nibble_3 = value_2 & 0xFFF;
    return ((value_1_nibble_3 + value_2_nibble_3) & 0x1000) == 0x1000;
}

bool Bytes::isCarrySub_8_three(uint8 value_1, uint8 value_2, uint8 value_3) {
    int16 result = value_1 - value_2 - value_3;
    return result < 0;
}

bool Bytes::isCarryAdd_8(uint8 value_1, uint8 value_2) {
    uint16 result = value_1 + value_2;
    return result > 255;
}

bool Bytes::isCarryAdd_8_three(uint8 value_1, uint8 value_2, uint8 value_3) {
    uint16 result = value_1 + value_2 + value_3;
    return result > 255;
}

bool Bytes::isCarryAdd_16(uint16 value_1, uint16 value_2) {
    uint32 result = value_1 + value_2;
    return result > 65535;
}

uint8 Bytes::wrappingAdd_8(uint8 value, uint8 add) {
    uint16 result = value + add;
    if(result > 255) {
        return result - 256;
    }
    return result;
}

uint16 Bytes::wrappingAdd_16(uint16 value, uint16 add) {
    uint32 result = value + add;
    if(result > 65535) {
        return result - 65536;
    }
    return result;
}

uint8 Bytes::wrappingSub_8(uint8 value, uint8 sub) {
    return value - sub;
}

uint16 Bytes::wrappingSub_16(uint16 value, uint16 sub) {
    return value - sub;
}

uint8 Bytes::rotateRight_8(uint8 value, uint8 n) {
    return ((value >> n) | (value << (8 - n))) & 0xFF;
}

uint8 Bytes::rotateLeft_8(uint8 value, uint8 n) {
    return ((((value) << n) & 0xFF) | (value >> (8 - n))) & 0xFF;
}

int8 Bytes::toSigned_8(uint8 value) {
    return value;
}
