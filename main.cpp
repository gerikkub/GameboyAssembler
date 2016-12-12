
#include <iostream>
#include <fstream>
#include <set>

#include "config.h"
#include "asm.h"
#include "Instruction.h"
#include "Parser.h"
#include "Label.h"

void printUsage()
{
    std::cout << "Usage: gbasm asmFile.s outFile" << std::endl; 
}

int main(int argc, char** argv)
{
    char lineBuffer[MAX_LINE_LENGTH];
    std::ifstream inputFile;
    ParsedLine_t pLine;
    int currentLine = 1;
    int currentAddress = 0;

    if (argc < 2)
    {
        printUsage();
    }

    inputFile.open(argv[1], std::ifstream::in);

    initInstructionSet();

    while (inputFile.good())
    {
        Instruction* currInst;

        inputFile.getline(lineBuffer, MAX_LINE_LENGTH);
        pLine = parseLine(lineBuffer);

        switch(pLine.type)
        {
            case TYPE_COMMENT:
            case TYPE_EMPTY:
                break;

            case TYPE_INSTRUCTION:
                currInst = createInstruction(pLine.data.inst.opcode,
                                             pLine.data.inst.p[0],
                                             pLine.data.inst.p[1],
                                             pLine.data.inst.label);

                if (currInst == NULL)
                {
                    std::cout << "Unknown instruction on line " << currentLine << std::endl;
                    exit(1);

                } else if (!currInst->isValid())
                {
                    std::cout << "Invalid parameters for instruction on line " << currentLine << std::endl;
                    exit(1);
                } else {

                    addInstructionToSet(currInst, currentAddress);

                    currentAddress += currInst->size();
                }

                break;

            case TYPE_LABEL:
                std::cout << "Found Label" << std::endl;

                addLabelToList(pLine.data.label, currentAddress);

                break;

            case TYPE_DIRECTIVE:
                std::cout << "Found Directive" << std::endl;
                break;

            case TYPE_ERROR:
                std::cout << "Found Error!" << std::endl;
                break;
        }

        currentLine++;
    }

    std::set<InstructionEntry_t>::iterator iter = getInstructionSetIterator();

    std::ofstream ofs;

    while (iter != getInstructionSetEnd())
    {
        InstructionEntry_t entry = *iter;
        entry.inst->writeMachineCode(ofs);

        iter++;
    }

    return 0;
}
