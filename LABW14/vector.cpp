#include <fstream>
#include <iostream>

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

void print(std::vector<Member> members)
{
    for (uint16_t i = 0; i < members.size(); i++)
    {
        std::cout << "Member #" << i + 1 << "\n";
        std::cout << members.at(i);
    }
}

void binPrint(std::string file, std::vector<Member> storage)
{
    binInput(file, storage, true);
    print(storage);
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
            {
                if (!binReadMember(input, storage.at(i)))
                {
                    std::cerr << "Error at write Member #" << i + 1 << "!\n";
                }
            }
        }
        else
        {
            for (size_t i = 0; i < storage.size() && input.good(); i++)
            {
                if (!binReadMember(input, storage.at(i)))
                {
                    std::cerr << "Error at read Member #" << i + 1 << "!\n";
                }
            }
        }
    }

    else
    {
        std::cerr << "File not exist or corrupt\n";
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
        std::cerr << "File not exist or corrupt\n";

    output.close();
}