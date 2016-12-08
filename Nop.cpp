
#include <fstream>
#include <iostream>

#include "asm.h"
#include "Instruction.h"

bool Nop::isValid()
{
    // Nop has not parameters
    return (params[0] == PARAMETER_NONE && 
        params[1] == PARAMETER_NONE);
}

bool Nop::writeMachineCode(std::ofstream& outStream)
{
    std::cout << "Writing Nop Inst";

    return true;
}

int Nop::size()
{
    return 1;
}

