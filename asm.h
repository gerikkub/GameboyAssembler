#ifndef __ASM_H__
#define __ASM_H__

#include <set>

typedef enum {
    PARAMETER_NONE = 0,
    PARAMETER_INVALID,
    PARAMETER_B,
    PARAMETER_C,
    PARAMETER_D,
    PARAMETER_E,
    PARAMETER_H,
    PARAMETER_L,
    PARAMETER_A,
    PARAMETER_BC,
    PARAMETER_DE,
    PARAMETER_HL,
    PARAMETER_SP,
    PARAMETER_SP_IMM,
    PARAMETER_IMM,
    PARAMETER_ADDR_C,
    PARAMETER_ADDR_BC,
    PARAMETER_ADDR_DE,
    PARAMETER_ADDR_HL,
    PARAMETER_ADDR_HLP,
    PARAMETER_ADDR_HLM,
    PARAMETER_ADDR_IMM,
    PARAMETER_FLAG_C,
    PARAMETER_FLAG_Z,
    PARAMETER_FLAG_NC,
    PARAMETER_FLAG_NZ,
} Parameter;

typedef enum {
    INST_NOT_FOUND = 0,
    INST_NOP,
    INST_HALT,
    INST_STOP,
    INST_LOAD,
    INST_LOADH,
    INST_INC,
    INST_DEC,
    INST_RLCA,
    INST_RRCA,
    INST_RLA,
    INST_RRA,
    INST_DAA,
    INST_CPL,
    INST_SCF,
    INST_CCF,
    INST_ADD,
    INST_ADC,
    INST_SUB,
    INST_SBC,
    INST_AND,
    INST_XOR,
    INST_OR,
    INST_CP,
    INST_PUSH,
    INST_POP,
    INST_JR,
    INST_JP,
    INST_RET,
    INST_CALL,
    INST_RETI,
    INST_RST,
    INST_DI,
    INST_EI,
    INST_RLC,
    INST_RRC,
    INST_RL,
    INST_RR,
    INST_SLA,
    INST_SRA,
    INST_SWAP,
    INST_SRL,
    INST_BIT,
    INST_RES,
    INST_SET
} InstructionName;

void initInstructionSet();

bool paramIsReg(Parameter p);
bool paramIsReg16(Parameter p);
bool paramIsFlag(Parameter p);

// Parameter needs to be defined before Instruction
#include "Instruction.h"

typedef struct {
    Instruction* inst;
    int offset;
}  InstructionEntry_t;

bool addInstructionToSet(Instruction* inst, int offset);
std::set<InstructionEntry_t>::iterator getInstructionSetIterator();
std::set<InstructionEntry_t>::iterator getInstructionSetEnd();

Instruction* createInstruction(InstructionName inst, Parameter p1, Parameter p2, char* imm);

#endif
