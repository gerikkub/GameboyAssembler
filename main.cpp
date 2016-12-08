
#include <iostream>
#include <fstream>

#include "config.h"
#include "asm.h"
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

    if (argc < 2)
    {
        printUsage();
    }

    inputFile.open(argv[1], std::ifstream::in);

    while (inputFile.good())
    {
        inputFile.getline(lineBuffer, MAX_LINE_LENGTH);
        pLine = parseLine(lineBuffer);

        switch(pLine.type)
        {
            case TYPE_COMMENT:
            case TYPE_EMPTY:
                break;

            case TYPE_INSTRUCTION:
                std::cout << "Found Instruction" << std::endl;
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
    }

    return 0;
}
