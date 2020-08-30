//
// Created by matthew on 28/07/2020.
//

#include "BackgroundAttributes.h"
#include "Bytes.h"

BackgroundAttributes::BackgroundAttributes(u_int8_t data) {
    paletteNumber = data & 0x7;
    alternateBank = Bytes::getBit_8(data, 3);
    priority = Bytes::getBit_8(data, 7);
    flipX = Bytes::getBit_8(data, 5);
    flipY = Bytes::getBit_8(data, 6);
}
