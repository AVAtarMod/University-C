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
        std::cout << "\n";
        if (numberMembers < 1)
            std::cerr << "Number members less than 1\n";
    }

    std::vector<Member> members;
    members.reserve(numberMembers);
    for (uint32_t i = 0; i < numberMembers; i++)
    {
        std::cout << "Member " << i << std::endl;
        std::cin >> members.at(i);
    }
    return members;
}

void print(std::vector<Member> members)
{
    uint16_t numberMembers = members.size();
    for (uint16_t i = 0; i < numberMembers; i++)
    {
        std::cout << members.at(i);
    }
}

void binPrint(const char *file, std::vector<Member> storage)
{
    binInput(file, storage, true);
    print(storage);
}

void binInput(const char *file, std::vector<Member> storage, bool readUntilEof)
{
    std::ifstream input(file, std::ios::binary);

    if (input.good())
    {
        uint16_t size = storage.size();
        for (uint16_t i = 0; i < size && !input.eof(); i++)
        {
            bool lastFill = (i == size - 1u);
            if (lastFill && readUntilEof)
            {
                storage.reserve(size + 1u);
            }

            Member *current = &storage.at(i);
            input.read((char *)(current), sizeof(Member));
        }
    }

    else
    {
        std::cerr << "File not exist\n";
    }

    input.close();
}

void binOutput(const char *file, std::vector<Member> storage)
{
    std::ofstream output(file, std::ios_base::binary);

    if (output.good())
    {
        for (uint16_t i = 0; i < storage.size(); i++)
        {
            output.write(static_cast<const char *>(storage.at(i)), sizeof(Member));
        }
    }
    else
        std::cerr << "File not exist";

    output.close();
}