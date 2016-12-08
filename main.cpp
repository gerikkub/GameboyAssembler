
#include <iostream>
#include <fstream>

#include "config.h"
#include "asm.h"
#include "Instruction.h"
#include "Parser.h"

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

    if (argc < 2)
    {
        printUsage();
    }

    inputFile.open(argv[1], std::ifstream::in);

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
                } else if (!currInst->isValid())
                {
                    std::cout << "Invalid parameters for instruction on line " << currentLine << std::endl;
                }

                break;

            case TYPE_LABEL:
                std::cout << "Found Label" << std::endl;
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



    return 0;
}
