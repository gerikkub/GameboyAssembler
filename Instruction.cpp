
#include "asm.h"
#include "Instruction.h"

Instruction::Instruction(Parameter p1, Parameter p2, char* imm)
{
    this->params[0] = p1;
    this->params[1] = p2;
    strncpy(this->imm, imm, MAX_LABEL_LENGTH-1);
    this->imm[MAX_LABEL_LENGTH-1] = '\0';
}

