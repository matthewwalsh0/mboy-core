//
// Created by matthew on 03/08/2020.
//

#ifndef MY_APPLICATION_RAM_H
#define MY_APPLICATION_RAM_H

class Ram {
public:
    virtual u_int8_t get_8(u_int32_t address) { return 0; };
    virtual bool set_8(u_int32_t address, u_int8_t value) { return false; };
};

#endif //MY_APPLICATION_RAM_H