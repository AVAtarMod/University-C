#include <iostream>

#include "struct.h"
#include "vector.h"
#include "files.h"
#include "useful.h"

std::string menu();
void help();
void getLackData(bool inputExist, std::string &input, bool outputExist, std::string &output);
void handleActions(std::string choice, std::string fileIn, std::string fileOut);

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
                if (fileIn.find('\n') != fileIn.npos)
                    fileIn.replace(fileIn.find('\n'), 1, "\0");
            }
        }
        
        else if (arg == ou && argv[i + 1])
        {
            outputEntered = true;
            if (isFileExist(argv[i + 1]))
            {
                outputExist = true;
                fileOut = argv[i + 1];
                if (fileOut.find('\n') != fileOut.npos)
                    fileOut.replace(fileOut.find('\n'), 1, "\0");
            }
        }
    }

    bool canContinue = true;
    if (!inputEntered || !outputEntered || !inputExist || !outputExist)
    {
        help();
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
            canContinue = false;
        }
    }
    if (canContinue)
        handleActions(menu(), fileIn, fileOut);
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
        handleActions(menu(), fileIn, fileOut);
    }

    return 0;
}

std::string menu()
{
    std::string choice;
    std::string menu;
    menu =
        "Choice action:\n\t"
        "1)Add members\n\t"
        "2)Display list of the members\n\t"
        "3)Delete member\n\t"
        "4)Find member\n\t"
        "5)Sort members\n\t"
        "6)Filter members\n\t"
        "----------------\n\t"
        "7)Save to file\n\t"
        "8)Add members from file\n\t"
        "Enter (you can select several actions, ex 1 4 7): ";
    char *storage = new char[UINT8_MAX];
    printAndScan(menu.c_str(), storage, UINT8_MAX);
    choice = {storage};
    delete[] storage;
    return choice;
}

void handleActions(std::string choice, std::string fileIn, std::string fileOut)
{
    int choiceN = 1;
    std::vector<Member> members;
    while (choiceN == 1)
    {
        std::vector<std::string> acts;
        size_t previousNum = 0;
        uint8_t iActs = 0;
        uint8_t count = 0;
        for (size_t i = 1; i < choice.size() + 1u; i++)
        {
            if ((isspace(choice[i]) || choice[i] == '\0') && isdigit(choice[i - 1u]))
            {
                ++count;

                std::string number = choice.substr(previousNum, i - previousNum);
                acts.resize(count);
                acts.at(iActs) = number;
                previousNum = i + 1;

                ++iActs;
            }
        }

        for (std::string i : acts)
        {
            uint8_t act;
            try
            {
                act = atoi(i.c_str());
            }
            catch (const std::exception &e)
            {
                std::cerr << fgBrightRed << e.what() << reset << '\n';
            }
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
                std::cin.ignore();
                binInput(fileIn, members, readAll);
                break;
            case 9:
                break;

            default:
                std::cerr << fgRed << "Action " << act << " not recognized" << reset << "\n";
                break;
            }
        }
        choiceN = printAndScan<int>("All actions complete. Exit (0)  or Menu(1)? Enter: ");
        if (choiceN == 1)
            choice = menu();
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
        std::cin.ignore();
    }
    if (!outputExist)
    {
        std::cout << "Enter output file: " << fgBlue;
        std::cin >> output;
        std::cout << reset;
        std::cin.ignore();
    }
}
