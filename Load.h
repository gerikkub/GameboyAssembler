#ifndef __LOAD_H__
#define __LOAD_H__

#include <iostream>

#include "Instruction.h"

class Load : Instruction {
    public:
        bool isValid();

        //bool writeMachineCode(std::ofstream outStream);
};

#endif
