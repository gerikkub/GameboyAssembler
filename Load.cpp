
#include <iostream>
#include <fstream>

#include "asm.h"
#include "Instruction.h"

typedef enum {
    LD_PARAM_INVALID,
    LD_PARAM_R16_IMM,
    LD_PARAM_ADDR_R16_A,
    LD_PARAM_REG_IMM,
    LD_PARAM_ADDR_IMM_SP,
    LD_PARAM_A_ADDR_R16,
    LD_PARAM_R_R,
    LD_PARAM_R_ADDR_HL,
    LD_PARAM_ADDR_HL_R,
    LD_PARAM_ADDR_C_A,
    LD_PARAM_A_ADDR_C,
    LD_PARAM_HL_SP_IMM,
    LD_PARAM_SP_HL,
    LD_PARAM_ADDR_IMM_A,
    LD_PARAM_A_ADDR_IMM
} LoadParameterType;

LoadParameterType getLoadParameterType(Parameter params[2])
{
    LoadParameterType paramType = LD_PARAM_INVALID;

    if (paramIsReg16(params[0]) &&
        params[1] == PARAMETER_IMM)
    {
        paramType = LD_PARAM_R16_IMM;
    }  else if ((params[0] == PARAMETER_ADDR_BC ||
                 params[0] == PARAMETER_ADDR_DE ||
                 params[0] == PARAMETER_ADDR_HLP ||
                 params[0] == PARAMETER_ADDR_HLM) &&
                 params[1] == PARAMETER_A)
    {
        paramType = LD_PARAM_ADDR_R16_A;
    } else if ((paramIsReg(params[0]) ||
                params[0] == PARAMETER_ADDR_HL) &&
                params[1] == PARAMETER_IMM)
    {
        paramType = LD_PARAM_REG_IMM;
    } else if (params[0] == PARAMETER_ADDR_IMM &&
               params[1] == PARAMETER_SP)
    {
        paramType = LD_PARAM_ADDR_IMM_SP;
    } else if (params[0] == PARAMETER_A &&
              (params[1] == PARAMETER_ADDR_BC ||
               params[1] == PARAMETER_ADDR_DE ||
               params[1] == PARAMETER_ADDR_HLP ||
               params[1] == PARAMETER_ADDR_HLM))
    {
        paramType = LD_PARAM_A_ADDR_R16;
    } else if (paramIsReg(params[0]) &&
             paramIsReg(params[1]))
    {
        paramType = LD_PARAM_R_R;
    } else if (paramIsReg(params[0]) &&
               params[1] == PARAMETER_ADDR_HL)
    {
        paramType = LD_PARAM_R_ADDR_HL;
    } else if (params[0] == PARAMETER_ADDR_HL &&
               paramIsReg(params[1]))
    {
        paramType = LD_PARAM_ADDR_HL_R;
    } else if (params[0] == PARAMETER_ADDR_C &&
               params[1] == PARAMETER_A)
    {
        paramType = LD_PARAM_ADDR_C_A;
    } else if (params[0] == PARAMETER_A &&
               params[1] == PARAMETER_ADDR_C)
    {
        paramType = LD_PARAM_A_ADDR_C;
    } else if (params[0] == PARAMETER_HL &&
               params[1] == PARAMETER_SP_IMM)
    {
        paramType = LD_PARAM_HL_SP_IMM;
    } else if (params[0] == PARAMETER_SP &&
               params[1] == PARAMETER_HL)
    {
        paramType = LD_PARAM_SP_HL;
    } else if (params[0] == PARAMETER_ADDR_IMM &&
               params[1] == PARAMETER_A)
    {
        paramType = LD_PARAM_ADDR_IMM_A;
    } else if (params[0] == PARAMETER_A &&
               params[1] == PARAMETER_ADDR_IMM)
    {
        paramType = LD_PARAM_A_ADDR_IMM;
    }

    return paramType;
}

bool Load::isValid()
{
    LoadParameterType pType;

    pType = getLoadParameterType(this->params);
    return pType != LD_PARAM_INVALID;
}

bool Load::writeMachineCode(char* data, int offset)
{
    std::cout << "Write Load Instr" << std::endl;

    return true;
}

int Load::size()
{
    int length = 0;

    switch (getLoadParameterType(this->params))
    {
        case LD_PARAM_R16_IMM:
            length = 3;
            break;

        case LD_PARAM_ADDR_R16_A:
            length = 1;
            break;

        case LD_PARAM_REG_IMM:
            length = 2;
            break;

        case LD_PARAM_ADDR_IMM_SP:
            length = 3;
            break;

        case LD_PARAM_A_ADDR_R16:
            length = 1;
            break;

        case LD_PARAM_R_R:
            length = 1;
            break;

        case LD_PARAM_R_ADDR_HL:
            length = 1;
            break;

        case LD_PARAM_ADDR_HL_R:
            length = 1;
            break;

        case LD_PARAM_ADDR_C_A:
            length = 1;
            break;

        case LD_PARAM_A_ADDR_C:
            length = 1;
            break;

        case LD_PARAM_HL_SP_IMM:
            length = 2;
            break;

        case LD_PARAM_SP_HL:
            length = 1;
            break;

        case LD_PARAM_ADDR_IMM_A:
            length = 3;
            break;

        case LD_PARAM_A_ADDR_IMM:
            length = 3;
            break;

        default:
            length = 0;
            break;
    }

    return length;
}

