
#include "asm.h"

bool paramIsReg(Parameter p)
{
    switch(p)
    {
        case PARAMETER_B:
        case PARAMETER_C:
        case PARAMETER_D:
        case PARAMETER_E:
        case PARAMETER_H:
        case PARAMETER_L:
        case PARAMETER_A:
            return true;

        default:
            return false;
    }

    return false;
}

bool paramIsReg16(Parameter p)
{
    switch(p)
    {
        case PARAMETER_BC:
        case PARAMETER_DE:
        case PARAMETER_HL:
        case PARAMETER_SP:
            return true;

        default:
            return false;
    }

    return false;
}

bool paramIsFlag(Parameter p)
{
    switch(p)
    {
        case PARAMETER_FLAG_C:
        case PARAMETER_FLAG_Z:
        case PARAMETER_FLAG_NC:
        case PARAMETER_FLAG_NZ:
            return true;

        default:
            return false;
    }

    return false;
}

