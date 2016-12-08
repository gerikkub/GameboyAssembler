
#include <cstring>
#include <cctype>

#include "config.h"

#include "Parser.h"
#include "asm.h"

typedef struct {
    char str[MAX_INST_LENGTH];
    InstructionName name;
} InstructionLookup;

const InstructionLookup instLookupTable[] = {
    {"nop", INST_NOP},
    {"halt", INST_HALT},
    {"stop", INST_STOP},
    {"ld", INST_LOAD},
    {"ldh", INST_LOADH},
    {"inc", INST_INC},
    {"dec", INST_DEC},
    {"rlca", INST_RLCA},
    {"rrca", INST_RRCA},
    {"rla", INST_RLA},
    {"rra", INST_RRA},
    {"daa", INST_DAA},
    {"cpl", INST_CPL},
    {"scf", INST_SCF},
    {"ccf", INST_CCF},
    {"add", INST_ADD},
    {"adc", INST_ADC},
    {"sub", INST_SUB},
    {"sbc", INST_SBC},
    {"and", INST_AND},
    {"xor", INST_XOR},
    {"or", INST_OR},
    {"cp", INST_CP},
    {"push", INST_PUSH},
    {"pop", INST_POP},
    {"jr", INST_JR},
    {"jp", INST_JP},
    {"ret", INST_RET},
    {"call", INST_CALL},
    {"reti", INST_RETI},
    {"rst", INST_RST},
    {"di", INST_DI},
    {"ei", INST_EI},
    {"rlc", INST_RLC},
    {"rrc", INST_RRC},
    {"rl", INST_RL},
    {"rr", INST_RR},
    {"sla", INST_SLA},
    {"sra", INST_SRA},
    {"swap", INST_SWAP},
    {"srl", INST_SRL},
    {"bit", INST_BIT},
    {"res", INST_RES},
    {"set", INST_SET}
};

typedef struct {
    char str[MAX_PARAM_LENGTH];
    Parameter param;
} ParameterLookup;

const ParameterLookup paramLookupTable[] = {
    {"$b", PARAMETER_B},
    {"$c", PARAMETER_C},
    {"$d", PARAMETER_D},
    {"$e", PARAMETER_E},
    {"$h", PARAMETER_H},
    {"$l", PARAMETER_L},
    {"$a", PARAMETER_A},
    {"$bc", PARAMETER_BC},
    {"$de", PARAMETER_DE},
    {"$hl", PARAMETER_HL},
    {"$sp", PARAMETER_SP},
    {"c", PARAMETER_FLAG_C},
    {"z", PARAMETER_FLAG_Z},
    {"nc", PARAMETER_FLAG_NC},
    {"nz", PARAMETER_FLAG_NZ}
};

const ParameterLookup addrParamLookupTable[] = {
    {"($c)", PARAMETER_ADDR_C},
    {"($bc)", PARAMETER_ADDR_BC},
    {"($de)", PARAMETER_ADDR_DE},
    {"($hl)", PARAMETER_ADDR_HL},
    {"($hl+)", PARAMETER_ADDR_HLP},
    {"($hl-)", PARAMETER_ADDR_HLM}
};
    

static InstructionName getInstructionName(char* inst)
{
    int idx = 0;
    while (inst[idx])
    {
        inst[idx] = tolower(inst[idx]);
        idx++;
    }

    for (idx = 0; idx < sizeof(instLookupTable)/sizeof(instLookupTable[0]); idx++)
    {
        if (strcmp(inst, instLookupTable[idx].str) == 0)
        {
            return instLookupTable[idx].name;
        }
    }

    return INST_NOT_FOUND;
}

static Parameter parseParameter(char* paramStr)
{
    int idx;

    if (paramStr == NULL ||
        strlen(paramStr) == 0)
    {
        return PARAMETER_NONE;
    }

    idx = 0;
    while (paramStr[idx])
    {
        if (isalpha(paramStr[idx]))
        {
            paramStr[idx] = tolower(paramStr[idx]);
        }
        idx++;
    }

    if (paramStr[0] == '(')
    {
        // Check for address parameters
        for (idx = 0; idx < sizeof(addrParamLookupTable)/sizeof(addrParamLookupTable[0]); idx++)
        {
            if (strcmp(addrParamLookupTable[idx].str, paramStr) == 0)
            {
                return addrParamLookupTable[idx].param;
            }
        }

        return PARAMETER_ADDR_IMM;
    } else {
        for (idx = 0; idx < sizeof(paramLookupTable)/sizeof(paramLookupTable[0]); idx++)
        {
            if (strcmp(paramLookupTable[idx].str, paramStr) == 0)
            {
                return paramLookupTable[idx].param;
            }
        }

        if (strncmp(paramStr, "$sp+", 4) == 0)
        {
            return PARAMETER_SP_IMM;
        }

        return PARAMETER_IMM;
    }

    return PARAMETER_INVALID;
}

static DirectiveType parseDirective(char* dirStr)
{
    return DIR_LOCATION;
}

ParsedLine_t parseLine(char* lineChars)
{
    ParsedLine_t pLine;
    char* tok = strtok(lineChars, " ,");

    if (tok == NULL)
    {
        // Parsing Empty Lines
        pLine.type = TYPE_EMPTY;
    } else if (tok[0] == '#')
    {
        // Parsing Comments
        pLine.type = TYPE_COMMENT;
    } else if (tok[0] == '.')
    {
        // Parsing Directives
        DirectiveType d;

        d = parseDirective(&tok[1]);

        if (d == DIR_INVALID)
        {
            pLine.type = TYPE_ERROR;
            pLine.data.error = ERROR_INVALID_DIRECTIVE;
        } else {

            pLine.type = TYPE_DIRECTIVE;
            pLine.data.directive.dir = d;

            tok = strtok(NULL, "");
            
            if (tok != NULL)
            {
                strncpy(pLine.data.directive.param, tok, MAX_DIRECTIVE_PARAM_LENGTH - 1);
                pLine.data.directive.param[MAX_DIRECTIVE_PARAM_LENGTH-1] = '\0';
            } else {
                pLine.data.directive.param[0] = '\0';
            }
        }
    } else {
        // Instruction probably
        InstructionName instName;

        instName = getInstructionName(tok);
        if (instName == INST_NOT_FOUND)
        {
            if (tok[strlen(tok)-1] == ':')
            {
                pLine.type = TYPE_LABEL;
                strncpy(pLine.data.label, tok, strlen(tok) - 1);
                pLine.data.label[strlen(tok)] = '\0';
            } else {
                pLine.type = TYPE_ERROR;
                pLine.data.error = ERROR_INVALID_INST;
            }
        } else {
            // Found Instruction. Parse parameters
            Parameter p;

            pLine.type = TYPE_INSTRUCTION;
            pLine.data.inst.opcode = instName;
            
            tok = strtok(NULL, " ,");
            p = parseParameter(tok);

            if (p == PARAMETER_INVALID)
            {
                pLine.type = TYPE_ERROR;
                pLine.data.error = ERROR_INVALID_PARAMETER;
            } else {
                // First Parameter Parsed
                pLine.data.inst.p[0] = p;

                if (p == PARAMETER_SP_IMM)
                {
                    tok += strlen("$sp+");
                }

                if (p == PARAMETER_ADDR_IMM)
                {
                    int idx = 0;

                    tok += 1;
                    while (tok[idx])
                    {
                        if (tok[idx] == ')')
                        {
                            tok[idx] = '\0';
                        }
                        idx++;
                    }
                }

                if (p == PARAMETER_IMM ||
                    p == PARAMETER_SP_IMM ||
                    p == PARAMETER_ADDR_IMM)
                {
                    strncpy(pLine.data.inst.label, tok, MAX_LABEL_LENGTH - 1);
                    pLine.data.inst.label[MAX_LABEL_LENGTH-1] = '\0';
                }

                tok = strtok(NULL, " ,");
                p = parseParameter(tok);

                if (p == PARAMETER_INVALID)
                {
                    pLine.type = TYPE_ERROR;
                    pLine.data.error = ERROR_INVALID_PARAMETER;
                } else {
                    // Second Parameter Parsed
                    pLine.data.inst.p[1] = p;

                    if (p == PARAMETER_SP_IMM)
                    {
                        tok += strlen("$sp+");
                    }

                    if (p == PARAMETER_ADDR_IMM)
                    {
                        int idx = 0;

                        tok += 1;
                        while (tok[idx])
                        {
                            if (tok[idx] == ')')
                            {
                                tok[idx] = '\0';
                            }
                            idx++;
                        }
                    }


                    if (p == PARAMETER_IMM ||
                        p == PARAMETER_SP_IMM ||
                        p == PARAMETER_ADDR_IMM)
                    {
                        strncpy(pLine.data.inst.label, tok, MAX_LABEL_LENGTH - 1);
                        pLine.data.inst.label[MAX_LABEL_LENGTH-1] = '\0';
                    }
                }
            }
        }
    }

    return pLine;
}


