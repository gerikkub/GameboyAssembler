#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <iostream>

#include "asm.h"

class Instruction {
    public:

        Instruction(Parameter p1, Parameter p2, int imm1);

        virtual bool isValid() = 0;

        //virtual bool writeMachineCode(std::ofstream outStream) = 0;

    protected:
        Parameter params[2];
        int imm;

};

#endif
