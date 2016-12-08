
#include <iostream>
#include <fstream>

#include "asm.h"
#include "Instruction.h"
#include "Load.h"

bool Load::isValid()
{
    if (paramIsReg(params[0]) &&
        paramIsReg(params[1]))
    {
        return true;
    }

    return false;
}

//bool writeMachineCode(std::ofstream outStream)
//{
    //std::cout << "Write Load Instr" << std::endl;

    //return true;
//}

