//
// Created by matthew on 05/07/2020.
//

#include "Bytes.h"

u_int8_t Bytes::setBit_8(u_int8_t value, u_int8_t index) {
    return value | (1 << index);
}

u_int8_t Bytes::getBit_8(u_int8_t value, u_int8_t index) {
    return (value & (1 << index)) != 0;
}

u_int16_t Bytes::join_8(u_int8_t upper, u_int8_t lower) {
    return (upper << 8) | lower;
}

u_int8_t Bytes::split_16_upper(u_int16_t value) {
    return value >> 8;
}

u_int8_t Bytes::split_16_lower(u_int16_t value) {
    return value & 0x00FF;
}

u_int8_t Bytes::clearBit_8(u_int8_t value, u_int8_t index) {
    return value & ~(1 << index);
}

u_int8_t Bytes::join_4(u_int8_t upper, u_int8_t lower) {
    return upper << 4 | lower;
}

u_int32_t Bytes::join_32(u_int8_t first, u_int8_t second, u_int8_t third) {
    return ((first << 16) | (second << 8)) | third;
}

u_int8_t Bytes::split_8_upper(u_int8_t value) {
    return value >> 4;
}

u_int8_t Bytes::split_8_lower(u_int8_t value) {
    return value & 0x0F;
}

bool Bytes::isHalfCarrySub_8(u_int8_t value_1, u_int8_t value_2) {
    int8_t result = (value_1 & 0xF) - (value_2 & 0xF);
    return result < 0;
}

bool Bytes::isHalfCarrySub_8_three(u_int8_t value_1, u_int8_t value_2, u_int8_t value_3) {
    int16_t result = (value_1 & 0xF) - (value_2 & 0xF) - (value_3 & 0xF);
    return result < 0;
}

bool Bytes::isHalfCarryAdd_8(u_int8_t value_1, u_int8_t value_2) {
    return (((value_1 & 0xF) + (value_2 & 0xF)) & 0x10) == 0x10;
}

bool Bytes::isHalfCarryAdd_8_three(u_int8_t value_1, u_int8_t value_2, u_int8_t value_3) {
    return (((value_1 & 0xF) + (value_2 & 0xF) + (value_3 & 0xF)) & 0x10) == 0x10;
}

bool Bytes::isHalfCarryAdd_16(u_int16_t value_1, u_int16_t value_2) {
    u_int16_t value_1_nibble_3 = value_1 & 0xFFF;
    u_int16_t value_2_nibble_3 = value_2 & 0xFFF;
    return ((value_1_nibble_3 + value_2_nibble_3) & 0x1000) == 0x1000;
}

bool Bytes::isCarrySub_8_three(u_int8_t value_1, u_int8_t value_2, u_int8_t value_3) {
    int16_t result = value_1 - value_2 - value_3;
    return result < 0;
}

bool Bytes::isCarryAdd_8(u_int8_t value_1, u_int8_t value_2) {
    u_int16_t result = value_1 + value_2;
    return result > 255;
}

bool Bytes::isCarryAdd_8_three(u_int8_t value_1, u_int8_t value_2, u_int8_t value_3) {
    u_int16_t result = value_1 + value_2 + value_3;
    return result > 255;
}

bool Bytes::isCarryAdd_16(u_int16_t value_1, u_int16_t value_2) {
    u_int32_t result = value_1 + value_2;
    return result > 65535;
}

u_int8_t Bytes::wrappingAdd_8(u_int8_t value, u_int8_t add) {
    u_int16_t result = value + add;
    if(result > 255) {
        return result - 256;
    }
    return result;
}

u_int16_t Bytes::wrappingAdd_16(u_int16_t value, u_int16_t add) {
    u_int32_t result = value + add;
    if(result > 65535) {
        return result - 65536;
    }
    return result;
}

u_int8_t Bytes::wrappingSub_8(u_int8_t value, u_int8_t sub) {
    return value - sub;
}

u_int16_t Bytes::wrappingSub_16(u_int16_t value, u_int16_t sub) {
    return value - sub;
}

u_int8_t Bytes::rotateRight_8(u_int8_t value, u_int8_t n) {
    return ((value >> n) | (value << (8 - n))) & 0xFF;
}

u_int8_t Bytes::rotateLeft_8(u_int8_t value, u_int8_t n) {
    return ((((value) << n) & 0xFF) | (value >> (8 - n))) & 0xFF;
}

int8_t Bytes::toSigned_8(u_int8_t value) {
    return value;
}
