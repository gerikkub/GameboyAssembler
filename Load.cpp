
#include <iostream>
#include <fstream>

#include "asm.h"
#include "Instruction.h"

bool Load::isValid()
{
    bool valid = false;

    if (paramIsReg16(params[0]) &&
        params[1] == PARAMETER_IMM)
    {
        valid = true;
    }  else if ((params[0] == PARAMETER_ADDR_BC ||
                 params[0] == PARAMETER_ADDR_DE ||
                 params[0] == PARAMETER_ADDR_HLP ||
                 params[0] == PARAMETER_ADDR_HLM) &&
                 params[1] == PARAMETER_A)
    {
        valid = true;
    } else if ((paramIsReg(params[0]) ||
                params[0] == PARAMETER_ADDR_HL) &&
                params[1] == PARAMETER_IMM)
    {
        valid = true;
    } else if (params[0] == PARAMETER_ADDR_IMM &&
               params[1] == PARAMETER_SP)
    {
        valid = true;
    } else if (params[0] == PARAMETER_A &&
              (params[1] == PARAMETER_ADDR_BC ||
               params[1] == PARAMETER_ADDR_DE ||
               params[1] == PARAMETER_ADDR_HLP ||
               params[1] == PARAMETER_ADDR_HLM))
    {
        valid = true;
    } else if (paramIsReg(params[0]) &&
             paramIsReg(params[1]))
    {
        valid = true;
    } else if (paramIsReg(params[0]) &&
               params[1] == PARAMETER_ADDR_HL)
    {
        valid = true;
    } else if (params[0] == PARAMETER_ADDR_HL &&
               paramIsReg(params[1]))
    {
        valid = true;
    } else if (params[0] == PARAMETER_ADDR_C &&
               params[1] == PARAMETER_A)
    {
        valid = true;
    } else if (params[0] == PARAMETER_A &&
               params[1] == PARAMETER_ADDR_C)
    {
        valid = true;
    } else if (params[0] == PARAMETER_HL &&
               params[1] == PARAMETER_SP_IMM)
    {
        valid = true;
    } else if (params[0] == PARAMETER_SP &&
               params[1] == PARAMETER_HL)
    {
        valid = true;
    } else if (params[0] == PARAMETER_ADDR_IMM &&
               params[1] == PARAMETER_A)
    {
        valid = true;
    } else if (params[0] == PARAMETER_A &&
               params[1] == PARAMETER_ADDR_IMM)
    {
        valid = true;
    }

    return valid;
}

bool Load::writeMachineCode(std::ofstream& outStream)
{
    std::cout << "Write Load Instr" << std::endl;

    return true;
}

int Load::size()
{
    int length = 0;

    if (paramIsReg16(params[0]) &&
        params[1] == PARAMETER_IMM)
    {
        length = 3;
    }  else if ((params[0] == PARAMETER_ADDR_BC ||
                 params[0] == PARAMETER_ADDR_DE ||
                 params[0] == PARAMETER_ADDR_HLP ||
                 params[0] == PARAMETER_ADDR_HLM) &&
                 params[1] == PARAMETER_A)
    {
        length = 1;
    } else if ((paramIsReg(params[0]) ||
                params[0] == PARAMETER_ADDR_HL) &&
                params[1] == PARAMETER_IMM)
    {
        length = 2;
    } else if (params[0] == PARAMETER_ADDR_IMM &&
               params[1] == PARAMETER_SP)
    {
        length = 3;
    } else if (params[0] == PARAMETER_A &&
              (params[1] == PARAMETER_ADDR_BC ||
               params[1] == PARAMETER_ADDR_DE ||
               params[1] == PARAMETER_ADDR_HLP ||
               params[1] == PARAMETER_ADDR_HLM))
    {
        length = 1;
    } else if (paramIsReg(params[0]) &&
             paramIsReg(params[1]))
    {
        length = 1;
    } else if (paramIsReg(params[0]) &&
               params[1] == PARAMETER_ADDR_HL)
    {
        length = 1;
    } else if (params[0] == PARAMETER_ADDR_HL &&
               paramIsReg(params[1]))
    {
        length = 1;
    } else if (params[0] == PARAMETER_ADDR_C &&
               params[1] == PARAMETER_A)
    {
        length = 1;
    } else if (params[0] == PARAMETER_A &&
               params[1] == PARAMETER_ADDR_C)
    {
        length = 1;
    } else if (params[0] == PARAMETER_HL &&
               params[1] == PARAMETER_SP_IMM)
    {
        length = 2;
    } else if (params[0] == PARAMETER_SP &&
               params[1] == PARAMETER_HL)
    {
        length = 1;
    } else if (params[0] == PARAMETER_ADDR_IMM &&
               params[1] == PARAMETER_A)
    {
        length = 3;
    } else if (params[0] == PARAMETER_A &&
               params[1] == PARAMETER_ADDR_IMM)
    {
        length = 3;
    }

    return length;
}

