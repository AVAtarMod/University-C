#include <fstream>
#include <iostream>
#include <algorithm>

#include "vector.h"

std::vector<Member> userInput()
{
    uint32_t numberMembers = 0;
    while (numberMembers < 1)
    {
        std::cout << "Enter number members (must be greater than 0): ";
        std::cin >> numberMembers;

        if (numberMembers < 1)
            std::cerr << "Number members less than 1\n";
    }

    std::vector<Member> members(numberMembers);

    for (uint32_t i = 0; i < numberMembers; i++)
    {
        std::cout << "Member #" << i + 1 << std::endl;
        std::cin >> members.at(i);
    }
    return members;
}

void print(std::vector<Member> members, const char* text = "")
{
    std::cout << "========= Members" << text << " =========\n";
    for (uint16_t i = 0; i < members.size(); i++)
    {
        std::cout << "Member #" << i + 1 << "\n";
        std::cout << members.at(i) << "\n";
    }
    std::cout << "=========         =========" << std::endl;
}

void binPrint(std::string file, std::vector<Member> storage)
{
    binInput(file, storage, true);
    print(storage," from file");
}

void deleteMember(std::vector<Member> &storage)
{
    uint16_t numberMember;
    std::cout << "Choice number member for delete it (";
    for (uint16_t i = 0; i < storage.size(); i++)
    {
        std::cout << i << "; ";
    }
    std::cout << "\b\b)\nEnter: ";
    std::cin >> numberMember;
    std::cin.ignore(INT16_MAX, '\n');
    if (numberMember < storage.size())
        storage.erase(storage.begin() + numberMember);

    print(storage);
    std::string file;
    std::cout << "Enter name file[.txt] for output current members: ";
    std::cin >> file;
    txtOutput(file, storage);
}

void sort(std::vector<Member> &storage)
{
    uint32_t act;
    uint32_t sort;
    std::cout << "Avaliable actions:\n\t"
                 "1) Sort for age\n\t"
                 "[1]lesser,[2]bigger\n\t"
                 "Enter (ex 1 2 for bigger age): ";
    std::cin >> act >> sort;
    switch (act)
    {
    case 1:
        if (sort == 1)
            std::sort(storage.begin(), storage.end(), leastAge());
        else if (sort == 2)
            std::sort(storage.begin(), storage.end(), biggerAge());
        break;

    default:
        break;
    }

    print(storage);
    std::string file;
    std::cout << "Enter name file[.txt] for output current members: ";
    std::cin >> file;
    txtOutput(file, storage);
}

void binInput(std::string file, std::vector<Member> &storage, bool readUntilEof)
{
    std::ifstream input(file, std::ios::binary);

    if (input.good())
    {
        char sizeString[8];
        input.read(sizeString, 8);
        size_t sizeNumeric = static_cast<size_t>(atoi(sizeString));

        if (readUntilEof)
        {
            if (storage.size() != sizeNumeric)
                storage.resize(sizeNumeric);
            for (size_t i = 0; i < sizeNumeric && input.good(); i++)
                if (!binReadMember(input, storage.at(i)))
                    std::cerr << "Error at write Member #" << i + 1 << "!\n";
        }
        else
            for (size_t i = 0; i < storage.size() && input.good(); i++)
                if (!binReadMember(input, storage.at(i)))
                    std::cerr << "Error at read Member #" << i + 1 << "!\n";
    }

    else
    {
        std::cerr << "File" << file << " not exist or corrupt\n";
    }

    input.close();
}

void binOutput(std::string file, std::vector<Member> storage)
{
    std::ofstream output(file, std::ios_base::binary);

    if (output.good())
    {
        size_t sizeNumeric = storage.size();
        auto sizeBinary = numberBinary(sizeNumeric);

        output.write(sizeBinary.get(), sizeof(sizeNumeric));
        for (uint16_t i = 0; i < sizeNumeric; i++)
        {
            if (!binWriteMember(output, storage.at(i)))
            {
                std::cerr << "Error at write Member #" << i + 1 << "!\n";
            }
        }
    }
    else
        std::cerr << "File " << file << " not exist or corrupt\n";

    output.close();
}

void txtOutput(std::string file, std::vector<Member> str)
{
    std::ofstream txtOut(file);
    if (txtOut.good())
    {
        for (size_t i = 0; i < str.size(); i++)
            txtOut << str.at(i);
    }
    else
        std::cerr << "File " << file << " not exist or corrupt\n";

    txtOut.close();
}