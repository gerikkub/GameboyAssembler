
#include <iostream>
#include <fstream>

#include "asm.h"
#include "Instruction.h"

bool Halt::isValid()
{
    return params[0] == PARAMETER_NONE &&
           params[1] == PARAMETER_NONE;
}

bool Halt::writeMachineCode(std::ofstream& outStream)
{
    std::cout << "Writing Halt Inst" << std::endl;
    return true;
}

int Halt::size()
{
    return 1;
}

