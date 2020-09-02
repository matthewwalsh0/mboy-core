#include "VRAM.h"
#include "MemoryMap.h"

class DataHook : public MemoryHook {

private:
    u_int8_t* data;
    u_int8_t* bank;

public:
    DataHook(u_int8_t* data, u_int8_t* bank) {
        this->data = data;
        this->bank = bank;
    }

    u_int8_t get_8(u_int16_t address) {
        return get_8(address, *bank);
    }

    u_int8_t get_8(u_int16_t address, u_int8_t bank) {
        u_int16_t relative = address - ADDRESS_VRAM_START;
        return data[bank * VRAM_BANK_SIZE + relative];
    }

    bool set_8(u_int16_t address, u_int8_t value) {
        u_int16_t relative = address - ADDRESS_VRAM_START;
        data[*bank * VRAM_BANK_SIZE + relative] = value;
        return true;
    }
};

class BankHook : public MemoryHook {

private:
    u_int8_t* bank;

public:
    BankHook(u_int8_t* bank) {
        this->bank = bank;
    }

    u_int8_t get_8(u_int16_t address) {
        return *bank;
    }

    bool set_8(u_int16_t address, u_int8_t value) {
        *bank = value & 0x1;
        return true;
    }
};

VRAM::VRAM(MemoryRegister* memory) {
    MemoryHook* dataHook = (MemoryHook*) new DataHook(data, &bank);
    MemoryHook* bankHook = (MemoryHook*) new BankHook(&bank);

    memory->registerGetter(0x8000, 0x9FFF, dataHook);
    memory->registerGetter(ADDRESS_VRAM_BANK, bankHook);

    memory->registerSetter(0x8000, 0x9FFF, dataHook);
    memory->registerSetter(ADDRESS_VRAM_BANK, bankHook);
}