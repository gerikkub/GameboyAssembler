
#include <iostream>
#include <fstream>

#include "asm.h"
#include "Instruction.h"

bool Stop::isValid()
{
    return params[0] == PARAMETER_NONE &&
           params[1] == PARAMETER_NONE;
}

bool Stop::writeMachineCode(std::ofstream& outStream)
{
    std::cout << "Writing Stop Inst" << std::endl;
    return true;
}

int Stop::size()
{
    return 2;
}

