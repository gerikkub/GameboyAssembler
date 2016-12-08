#ifndef __PARSER_H__
#define __PARSER_H__

#include "config.h"

#include "asm.h"

typedef enum {
    ERROR_INVALID_INST,
    ERROR_INVALID_PARAMETER,
    ERROR_INVALID_DIRECTIVE
} ErrorType;

typedef enum {
    TYPE_EMPTY,
    TYPE_INSTRUCTION,
    TYPE_COMMENT,
    TYPE_LABEL,
    TYPE_DIRECTIVE,
    TYPE_ERROR
} LineType;

typedef enum {
    DIR_INVALID,
    DIR_LOCATION
} DirectiveType;

typedef struct {
    InstructionName opcode;
    Parameter p[2];
    char label[MAX_LABEL_LENGTH];
} InstructionInfo_t;

typedef struct {
    DirectiveType dir;
    char param[MAX_DIRECTIVE_PARAM_LENGTH];
} DirectiveInfo_t;

typedef struct {
    LineType type;
    union {
        InstructionInfo_t inst;
        char label[MAX_LABEL_LENGTH];
        DirectiveInfo_t directive;
        ErrorType error;
    } data;
} ParsedLine_t;

ParsedLine_t parseLine(char* lineChars);

#endif
