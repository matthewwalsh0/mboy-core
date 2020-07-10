//
// Created by matthew on 04/07/2020.
//

#include <stdexcept>
#include "Types.h"
#include "Bytes.h"
#include "CPU.h"
#include "Instructions.h"
#include "MemoryMap.h"

const uint16 STACK_POINTER_START = 0xFFFE;
const uint16 EXECUTION_START = 0x100;
const uint16 INTERRUPT_ROUTINE_VERTICAL_BLANK = 0x0040;
const uint16 INTERRUPT_ROUTINE_LCD = 0x0048;
const uint16 INTERRUPT_ROUTINE_TIMER = 0x0050;
const uint16 INTERRUPT_ROUTINE_SERIAL = 0x0058;
const uint16 INTERRUPT_ROUTINE_JOYPAD = 0x0060;
const std::string LOG_PATH = "/sdcard/Download/matterboy_log_cpu.txt";

CPU::CPU() : logFile(LOG_PATH) {
    a = 0x11;
    b = 0x00;
    c = 0x13;
    d = 0x00;
    e = 0xD8;
    h = 0x01;
    l = 0x4D;
    sp = STACK_POINTER_START;
    pc = EXECUTION_START;
    flag_z = true;
    flag_n = false;
    flag_h = true;
    flag_c = true;
    interruptsEnabled = false;
    halt = false;
    swapSpeed = false;
    currentSpeed = 1;
}

uint8 CPU::get_8(Register cpuRegister) {
    switch(cpuRegister) {
        case A:
            return a;
        case B:
            return b;
        case C:
            return c;
        case D:
            return d;
        case E:
            return e;
        case H:
            return h;
        case L:
            return l;
        default:
            return 0;
    }
}

uint8 CPU::get_f() {
    uint8 value = 0x0;
    if(flag_z) { value = Bytes::setBit_8(value, 7); }
    if(flag_n) { value = Bytes::setBit_8(value, 6); }
    if(flag_h) { value = Bytes::setBit_8(value, 5); }
    if(flag_c) { value = Bytes::setBit_8(value, 4); }
    return value;
}

void CPU::set_f(uint8 value) {
    flag_z = Bytes::getBit_8(value, 7);
    flag_n = Bytes::getBit_8(value, 6);
    flag_h = Bytes::getBit_8(value, 5);
    flag_c = Bytes::getBit_8(value, 4);
}

uint16 CPU::get_16(Register cpuRegister) {
    switch(cpuRegister) {
        case BC:
            return Bytes::join_8(b, c);
        case DE:
            return Bytes::join_8(d, e);
        case HL:
            return Bytes::join_8(h, l);
        case AF:
            return Bytes::join_8(a, get_f());
        default:
            throw std::invalid_argument("Invalid 16-bit read from CPU.");
    }
}

void CPU::set_8(Register cpuRegister, uint8 value) {
    switch(cpuRegister) {
        case A:
            a = value;
            return;
        case B:
            b = value;
            return;
        case C:
            c = value;
            return;
        case D:
            d = value;
            return;
        case E:
            e = value;
            return;
        case H:
            h = value;
            return;
        case L:
            l = value;
            return;
        default:
            throw std::invalid_argument("Invalid write to CPU.");
    }
}

void CPU::set_16(Register cpuRegister, uint16 value) {
    uint8 upper = Bytes::split_16_upper(value);
    uint8 lower = Bytes::split_16_lower(value);

    switch(cpuRegister) {
        case BC:
            b = upper;
            c = lower;
            return;
        case DE:
            d = upper;
            e = lower;
            return;
        case HL:
            h = upper;
            l = lower;
            return;
        case AF:
            a = upper;
            set_f(lower);
            return;
        default:
            throw std::invalid_argument("Invalid 16-bit write to CPU.");
    }
}

uint16 CPU::step(Memory* memory, uint32 count, bool debug) {
    uint8 instructionCode = memory->get_8(pc);
    uint8 arg_1 = 0;
    uint8 arg_2 = 0;
    uint8 arg_8 = 0;
    uint16 arg_16 = 0;

    if(instructionCode == 0xCB) {
        arg_1 = memory->get_8(pc + 1);
        arg_8 = arg_1;
    }

    instructionInfo instruction = Instructions::getInfo(instructionCode, arg_8);
    uint8 instructionLength = instruction.length;

    if(instructionLength > 1) {
        arg_1 = memory->get_8(pc + 1);
        arg_8 = arg_1;
    }

    if(instructionLength > 2) {
        arg_2 = memory->get_8(pc + 2);
        arg_16 = Bytes::join_8(arg_2, arg_1);
    }

    uint16 instructionDurationAction = instruction.cyclesAction;
    uint16 instructionDurationNoAction = instruction.cyclesNoAction;
    uint16 totalCycles = 0;

    //uint8 argLength = instruction.length - 1;

//    logFile.write("%d - 0x%04X - 0x%04X - %10s - %02X - %04X - AF=%04X BC=%04X DE=%04X HL=%04X SP=%04X - Z=%d N=%d H=%d C=%d",
//                  count, pc, instructionCode, instruction.debug, arg_8, arg_16,
//                  get_16(AF), get_16(BC), get_16(DE), get_16(HL), sp,
//                  flag_z, flag_n, flag_h, flag_c);

    if(!halt) {
        pc += instructionLength;
        bool action = Instructions::run(instructionCode, this, memory, arg_8, arg_16);
        uint16 interruptCycles = checkInterrupts(memory);
        uint16 instructionCycles = action ? instructionDurationAction : instructionDurationNoAction;
        totalCycles = instructionCycles + interruptCycles;
    } else {
        totalCycles = 12 + checkInterrupts(memory);
    }

    return totalCycles / currentSpeed;
}

uint8 CPU::getInterruptEnable() {
    uint8 value = 0;

    if(interruptEnableVerticalBlank) value = Bytes::setBit_8(value, 0);
    if(interruptEnableLcd) value = Bytes::setBit_8(value, 1);
    if(interruptEnableTimer) value = Bytes::setBit_8(value, 2);
    if(interruptEnableSerial) value = Bytes::setBit_8(value, 3);
    if(interruptEnableJoypad) value = Bytes::setBit_8(value, 4);

    return value;
}

uint8 CPU::getInterruptFlags() {
    uint8 value = 0;

    if(interruptFlagsVerticalBlank) value = Bytes::setBit_8(value, 0);
    if(interruptFlagsLcd) value = Bytes::setBit_8(value, 1);
    if(interruptFlagsTimer) value = Bytes::setBit_8(value, 2);
    if(interruptFlagsSerial) value = Bytes::setBit_8(value, 3);
    if(interruptFlagsJoypad) value = Bytes::setBit_8(value, 4);

    return value;
}

void CPU::setInterruptEnable(uint8 value) {
    interruptEnableVerticalBlank = Bytes::getBit_8(value, 0);
    interruptEnableLcd = Bytes::getBit_8(value, 1);
    interruptEnableTimer = Bytes::getBit_8(value, 2);
    interruptEnableSerial = Bytes::getBit_8(value, 3);
    interruptEnableJoypad = Bytes::getBit_8(value, 4);
}

void CPU::setInterruptFlags(uint8 value) {
    interruptFlagsVerticalBlank = Bytes::getBit_8(value, 0);
    interruptFlagsLcd = Bytes::getBit_8(value, 1);
    interruptFlagsTimer = Bytes::getBit_8(value, 2);
    interruptFlagsSerial = Bytes::getBit_8(value, 3);
    interruptFlagsJoypad = Bytes::getBit_8(value, 4);
}

void CPU::flagInterrupt(uint8 bit) {
    switch(bit) {
        case 0:
            interruptFlagsVerticalBlank = true;
            return;
        case 1:
            interruptFlagsLcd = true;
            return;
        case 2:
            interruptFlagsTimer = true;
            return;
        case 3:
            interruptFlagsSerial = true;
            return;
        case 4:
            interruptFlagsJoypad = true;
            return;
        default:
            throw std::invalid_argument("Invalid interrupt flag.");
    }
}

uint16 CPU::checkInterrupts(Memory* memory) {
    if (!halt && !interruptsEnabled) {
        return 0;
    }

    uint16 target = 0;

    if (interruptEnableVerticalBlank && interruptFlagsVerticalBlank) {
        target = INTERRUPT_ROUTINE_VERTICAL_BLANK;
    } else if (interruptEnableLcd && interruptFlagsLcd) {
        target = INTERRUPT_ROUTINE_LCD;
    } else if (interruptEnableTimer && interruptFlagsTimer) {
        target = INTERRUPT_ROUTINE_TIMER;
    } else if (interruptEnableSerial && interruptFlagsSerial) {
        target = INTERRUPT_ROUTINE_SERIAL;
    } else if (interruptEnableJoypad && interruptFlagsJoypad) {
        target = INTERRUPT_ROUTINE_JOYPAD;
    }

    if (target != 0) {
        halt = false;

        if (interruptsEnabled) {
            interruptsEnabled = false;
            setInterruptFlags(0);
            Instructions::call(this, memory, target);
            return 20;
        }

        return 0;
    }

    return 0;
}

uint8 CPU::get_8(uint16 address) {
    switch(address) {
        case ADDRESS_INTERRUPT_ENABLE:
            return getInterruptEnable();
        case ADDRESS_INTERRUPT_FLAGS:
            return getInterruptFlags();
        default:
            throw std::invalid_argument("Invalid read from CPU.");
    }
}

bool CPU::set_8(uint16 address, uint8 value) {
    switch(address) {
        case ADDRESS_INTERRUPT_ENABLE:
            setInterruptEnable(value);
            return true;
        case ADDRESS_INTERRUPT_FLAGS:
            setInterruptFlags(value);
            return true;
        default:
            throw std::invalid_argument("Invalid write to CPU.");
    }
}

void CPU::flag_interrupt(uint8 bit) {
    flagInterrupt(bit);
}
