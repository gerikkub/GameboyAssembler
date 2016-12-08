
#include "asm.h"
#include "Instruction.h"

Instruction::Instruction(Parameter p1, Parameter p2, int imm)
{
    this->params[0] = p1;
    this->params[1] = p2;
    this->imm = imm;
}

