//
// Created by matthew on 06/07/2020.
//

#ifndef MY_APPLICATION_GUI_H
#define MY_APPLICATION_GUI_H

#include "Types.h"

class GUI {
public:
    virtual void displayBuffer(uint32* pixels) {};
    virtual bool isOpen() { return true; }
    virtual void displayFPS(uint16 fps) {};
};


#endif //MY_APPLICATION_GUI_H
