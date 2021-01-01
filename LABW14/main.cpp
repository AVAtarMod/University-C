#include <iostream>

#include "struct.h"
#include "vector.h"
#include "files.h"
#include "useful.h"

void menu();
void help();
void getLackData(bool inputExist, std::string &input, bool outputExist, std::string &output);

int main(int argc, char const *argv[])
{
    bool inputEntered = false;
    bool inputExist = false;
    bool outputEntered = false;
    bool outputExist = false;

    std::string fileIn;
    std::string fileOut;
    std::string in = "-i";
    std::string ou = "-o";

    for (int i = 1; i < argc; i += 2)
    {
        std::string arg = argv[i];
        std::string nextArg = argv[i + 1];
        if (arg == in && argv[i + 1])
        {
            inputEntered = true;
            if (isFileExist(argv[i + 1]))
            {
                inputExist = true;
                fileIn = argv[i + 1];
            }
        }
        else if (arg == ou && argv[i + 1])
        {
            outputEntered = true;
            if (isFileExist(argv[i + 1]))
            {
                outputExist = true;
                fileIn = argv[i + 1];
            }
        }
    }

    bool canContinue = true;
    if (!inputEntered || !outputEntered || !inputExist || !outputExist)
    {
        if (inputEntered && !inputExist)
        {
            std::cerr << fgRed << "File (input): file not exist or no rights to open it"
                      << reset << "\n";
            canContinue = false;
        }
        if (outputEntered && !outputExist)
        {
            std::cerr << fgRed << "File (output): file not exist or no rights to open it"
                      << reset << "\n";
            canContinue = false;
        }
        if (!inputEntered || !outputEntered)
        {
            std::cerr << fgYellow << "File for output or input not entered. You'll need to enter this data soon."
                      << reset << "\n";
            canContinue = true;
        }
    }
    if (canContinue)
        menu();
    else
    {
        while (!isFileExist(fileIn.c_str()))
        {
            getLackData(inputExist, fileIn, outputExist, fileOut);
            if (!isFileExist(fileIn.c_str())) std::cout << fgRed << "Oops. Input file incorrect." << reset << "\n";
        }
        std::cout <<"----------------\n" <<fgGreen << "Sucess! Files correct." << reset <<  ((isFileExist(fileOut.c_str())) ? " " : "The output file will create if you do save data.") << "\n";
        menu();
    }

    return 0;
}

void menu()
{
    uint16_t choice;
    std::cout << "Choice act:\n\t"
                 "1)Add member\n\t"
                 "2)Display list of the members\n\t"
                 "3)Delete member\n\t"
                 "4)Find member\n\t"
                 "5)Sort members\n\t"
                 "6)Filter members\n\t"
                 "----------------\n\t"
                 "7)Save to file\n\t"
                 "8)Add members from file\n"
                 "Enter: ";
    std::cin >> choice;
}

void help()
{
    std::cout << "Arguments:\n\t'-i <file>' - input file. It need for geting list members.\n\t'-o <file>' - output file. It need for save entered members.\n";
}

void getLackData(bool inputExist, std::string &input, bool outputExist, std::string &output)
{
    if (!inputExist)
    {
        std::cout << "Enter input file: " << fgBlue;
        std::cin >> input;
        std::cout << reset;
    }
    if (!outputExist)
    {
        std::cout << "Enter output file: " << fgBlue;
        std::cin >> output;
        std::cout << reset;
    }
}
