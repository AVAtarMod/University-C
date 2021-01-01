#include <iostream>

#include "struct.h"
#include "vector.h"
#include "files.h"
#include "useful.h"

void menu(std::string fileIn, std::string fileOut);
void help();
void getLackData(bool inputExist, std::string &input, bool outputExist, std::string &output);
void handleActions(uint32_t choice, std::string fileIn, std::string fileOut);

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
        menu(fileIn, fileOut);
    else
    {
        while (!isFileExist(fileIn.c_str()))
        {
            getLackData(inputExist, fileIn, outputExist, fileOut);
            if (!isFileExist(fileIn.c_str()))
                std::cout << fgRed << "Oops. Input file incorrect." << reset << "\n";
        }
        std::cout << "----------------\n"
                  << fgGreen << "Sucess! Files correct." << reset << ((isFileExist(fileOut.c_str())) ? " " : "The output file will create if you do save data.") << "\n";
        menu(fileIn, fileOut);
    }

    return 0;
}

void menu(std::string fileIn, std::string fileOut)
{
    std::cout << "Choice action:\n\t"
                 "1)Add members\n\t"
                 "2)Display list of the members\n\t"
                 "3)Delete member\n\t"
                 "4)Find member\n\t"
                 "5)Sort members\n\t"
                 "6)Filter members\n\t"
                 "----------------\n\t"
                 "7)Save to file\n\t"
                 "8)Add members from file\n"
                 "Enter (you can select several actions, ex 147): ";

    uint32_t choice;
    std::cin >> choice;
    handleActions(uint32_t(reverseNumber(int(choice))), fileIn, fileOut);
}

void handleActions(uint32_t choice, std::string fileIn, std::string fileOut)
{
    std::vector<Member> members;
    while (choice != 0u)
    {
        uint8_t act = choice % 10u;
        switch (act)
        {
        case 1:
            members = userInput();
            break;
        case 2:
            print(members);
            break;
        case 3:

            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            binOutput(fileOut, members);
            break;
        case 8:
            bool readAll;
            std::cout << "Read all file (1 = yes, 0 = no)? Enter: ";
            std::cin >> readAll;
            binInput(fileIn, members, readAll);
            break;

        default:
            std::cerr << fgRed << "Action " << act << " not recognized" << reset << "\n";
            break;
        }
        choice /= 10u;
    }
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
