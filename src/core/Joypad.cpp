#include "Joypad.h"

#include "Bytes.h"
#include "GUI.h"
#include "MemoryMap.h"
#include "MemoryRegister.h"

static u_int8_t get_8(GUI* gui, u_int16_t column) {
    u_int8_t value = column | 0x0F;
    bool buttonStart = false;
    bool buttonSelect = false;
    bool buttonA = false;
    bool buttonB = false;
    bool buttonUp = false;
    bool buttonDown = false;
    bool buttonLeft = false;
    bool buttonRight = false;

    switch(column) {
        case 0:
            buttonStart = gui->isDown(BUTTON_START);
            buttonSelect = gui->isDown(BUTTON_SELECT);
            buttonA = gui->isDown(BUTTON_A);
            buttonB = gui->isDown(BUTTON_B);

            if (buttonA) { value = Bytes::clearBit_8(value, 0); }
            if (buttonB) { value = Bytes::clearBit_8(value, 1); }
            if (buttonSelect) { value = Bytes::clearBit_8(value, 2); }
            if (buttonStart) { value = Bytes::clearBit_8(value, 3); }
            break;
        case 1:
            buttonUp = gui->isDown(BUTTON_UP);
            buttonDown = gui->isDown(BUTTON_DOWN);
            buttonLeft = gui->isDown(BUTTON_LEFT);
            buttonRight = gui->isDown(BUTTON_RIGHT);

            if (buttonRight) { value = Bytes::clearBit_8(value, 0); }
            if (buttonLeft) { value = Bytes::clearBit_8(value, 1); }
            if (buttonUp) { value = Bytes::clearBit_8(value, 2); }
            if (buttonDown) { value = Bytes::clearBit_8(value, 3); }
            break;
    }

    return value;
}

static bool set_8(u_int8_t* column, u_int8_t value) {
    u_int8_t columnValue = value & 0x30;
    bool column_1 = Bytes::getBit_8(columnValue, 4);
    bool column_2 = Bytes::getBit_8(columnValue, 5);

    if(column_1) {
        *column = 0;
    } else if(column_2) {
        *column = 1;
    }

    return true;
}

Joypad::Joypad(GUI *gui, Memory* memory) {
    this->gui = gui;

    memory->registerGetter(ADDRESS_JOYPAD, [this]MEMORY_GETTER_LAMBDA {
        return get_8(this->gui, column);
    });

    memory->registerSetter(ADDRESS_JOYPAD, [this]MEMORY_SETTER_LAMBDA {
        return set_8(&column, value);
    });
}
