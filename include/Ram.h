//
// Created by matthew on 03/08/2020.
//

#ifndef MY_APPLICATION_RAM_H
#define MY_APPLICATION_RAM_H

class Ram {
public:
    virtual uint8 get_8(uint32 address) { return 0; };
    virtual bool set_8(uint32 address, uint8 value) { return false; };
};

#endif //MY_APPLICATION_RAM_H