#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <iostream>
#include <cstring>

#include "config.h"

class Instruction {
    public:

        Instruction(Parameter p1, Parameter p2, char* imm);

        virtual bool isValid() = 0;

        virtual bool writeMachineCode(char* data, int offset) = 0;

        virtual int size() = 0;

    protected:
        Parameter params[2];
        char imm[MAX_LABEL_LENGTH];

};

class Nop : public Instruction {
    public:
        Nop(Parameter p1, Parameter p2, char* imm)
            : Instruction(p1, p2, imm) { }

        bool isValid();
        bool writeMachineCode(char* data, int offset);
        int size();
};

class Halt : public Instruction {
    public:
        Halt(Parameter p1, Parameter p2, char* imm)
            : Instruction(p1, p2, imm) { }

        bool isValid();
        bool writeMachineCode(char* data, int offset);
        int size();
};

class Stop : public Instruction {
    public:
        Stop(Parameter p1, Parameter p2, char* imm)
            : Instruction(p1, p2, imm) { }

        bool isValid();
        bool writeMachineCode(char* data, int offset);
        int size();
};

class Load : public Instruction {
    public:
        Load(Parameter p1, Parameter p2, char* imm)
            : Instruction(p1, p2, imm) { }

        bool isValid();
        bool writeMachineCode(char* data, int offset);
        int size();
};

#endif
