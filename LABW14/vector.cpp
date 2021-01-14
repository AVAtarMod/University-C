#include <fstream>
#include <iostream>
#include <algorithm>

#include "vector.h"
namespace COLORS
{
    #include "useful.h"
} // namespace COLORS


void userInput(std::vector<Member> &storage)
{
    uint32_t numberMembers = 0;
    while (numberMembers < 1)
    {
        std::cout << "Enter number members: ";
        std::cin >> numberMembers;

        if (numberMembers < 1)
            std::cerr << COLORS::fgBrightRed << "Number members less than 1\n";
    }

    uint32_t pos = 0;
    while (pos > storage.size() && !storage.empty())
    {
        std::cout << "Enter position (you can choice from ";
        for (uint16_t i = 0; i < storage.size() + 1; i++)
            std::cout << i << "; ";
        std::cout << "\b\b ): ";

        std::cin >> pos;

        if (pos < 1)
            std::cerr << COLORS::fgBrightRed << "Position greater than " << storage.size() + 1 << "\n";
    }

    storage.resize(numberMembers);

    for (uint32_t i = pos; i < numberMembers; i++)
    {
        std::cout << "Member #" << i + 1 << std::endl;
        if (pos == storage.size() + 1)
            storage.reserve(storage.size() + 1);
        std::cin >> storage.at(i);
    }
}

void print(std::vector<Member> members, const char *text)
{
    std::cout <<  COLORS::fgGreen << "========= Members" << text << " =========" << COLORS::reset << "\n";
    for (uint16_t i = 0; i < members.size(); i++)
    {
        std::cout << "Member #" << i + 1 << "\n";
        std::cout << members.at(i) << "\n";
    }
    std::cout <<  COLORS::fgGreen << "========="<< COLORS::reset << std::endl;
}

void deleteElement(std::vector<Member> &storage)
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

    finalAct(storage);
}

void edit(std::vector<Member> &storage)
{
    uint16_t numberMember;
    std::cout << "Choice number member for edit it (";
    for (uint16_t i = 0; i < storage.size(); i++)
    {
        std::cout << i + 1 << "; ";
    }
    std::cout << "\b\b)\nEnter: ";
    std::cin >> numberMember;
    if (numberMember -1 < storage.size())
        editMember(storage.at(numberMember - 1));

    finalAct(storage," (после редактирования)");
}

void sort(std::vector<Member> &storage)
{
    uint32_t act;
    uint32_t sort;
    std::cout << "Avaliable actions:\n\t"
                 "1) Sort for full name [1]A-Z [2]Z-A \n\t"
                 "Enter (ex 1 2 for sort A-Z (fullName)): ";
    std::cin >> act >> sort;
    switch (act)
    {
    case 1:
        if (sort == 1)
            std::sort(storage.begin(),storage.end(),sortFullnameA_Z);
        else if (sort == 2)
            std::sort(storage.begin(), storage.end(),sortFullnameZ_A);
        else std::cerr << COLORS::fgBrightRed << "You not entered 2 option or enter incorrect value" << COLORS::reset << "\n";
        break;
    default:
        break;
    }

    finalAct(storage);
}

void find(std::vector<Member> storage)
{
    std::cout << "Avaliable actions:\n\t"
                 "1) Find by work\n\t"
                 "2) Find by country\n\t"
                 "3) Find by age\n\t"
                 "NOTE: add '0' to your action for search invert.\n";
    uint32_t act = 0;
    std::cout << "  Enter action: ";
    std::cin >> act;
    std::vector<Member> result;
    while (act != 4)
    {
        std::string data;
        char buffer[STR_SIZE];

        switch (act)
        {
        case 1:
            std::cin.ignore(INT16_MAX,'\n');
            std::cout << "  Enter work: ";
            std::cin.getline(buffer,STR_SIZE);
            data = {buffer};
            for (size_t i = 0; i < storage.size(); i++)
            {
                if (searchText(storage.at(i).work,data.c_str()))
                    result.push_back(storage.at(i));
            }
            break;
        case 2:
            std::cin.ignore(INT16_MAX,'\n');
            std::cout << "  Enter country: ";
            std::cin.getline(buffer,STR_SIZE);
            data = {buffer};
            for (size_t i = 0; i < storage.size(); i++)
            {
                if (searchText(storage.at(i).country,data.c_str()))
                    result.push_back(storage.at(i));
            }
            break;
        case 20: 
            std::cin.ignore(INT16_MAX,'\n');
            std::cout << "  Enter your country: ";
            std::cin.getline(buffer,STR_SIZE);
            data = {buffer};
            for (size_t i = 0; i < storage.size(); i++)
            {
                if (!searchText(storage.at(i).country,data.c_str()))
                    result.push_back(storage.at(i));
            }
            break;
        case 3:
            std::cout << "Avaliable actions:\n\t"
                    "1) Find youngest\n\t"
                    "Enter: ";
            std::cin >> act;
            if (act == 1){
                std::sort(storage.begin(),storage.end(),
                [](Member &a,Member &b)
                {return (a.age <= b.age);});

                result.push_back(storage.at(0));}
            break;
        default:
            break;
        }
        storage = result;
        storage.resize(result.size());
        result.resize(0);
        std::cout << "  Do you want exit? [4]Yes [1-3]Continue finding.\n";
        std::cout << "  Enter action: ";
        std::cin >> act;
    }
    finalAct(storage," (searched)");
}

void binPrint(std::string file, std::vector<Member> storage)
{
    binInput(file, storage, true);
    print(storage, " from file");
}

void binInput(std::string file, std::vector<Member> &storage, bool readUntilEof)
{
    std::ifstream input(file, std::ios::binary);

    if (input.good())
    {
        char sizeString[8];
        input.read(sizeString, 8);
        size_t sizeNumeric = *((size_t*)sizeString); 

        if (readUntilEof)
        {
            if (storage.size() != sizeNumeric)
                storage.resize(sizeNumeric);
            for (size_t i = 0; i < sizeNumeric && input.good(); i++)
                if (!binReadMember(input, storage.at(i)))
                    std::cerr << COLORS::fgBrightRed << "Error at write Member #" << i + 1 << "!"<< COLORS::reset << "\n";
        }
        else
            for (size_t i = 0; i < storage.size() && input.good(); i++)
                if (!binReadMember(input, storage.at(i)))
                    std::cerr << COLORS::fgBrightRed << "Error at read Member #" << i + 1 << "!"<< COLORS::reset << "\n";
    }

    else
    {
        std::cerr << COLORS::fgBrightRed << "File" << file << " not exist or corrupt"<< COLORS::reset << "\n";
    }

    input.close();
}

void binOutput(std::string file, std::vector<Member> storage)
{
    std::ofstream output(file, std::ios_base::binary);

    if (output.good())
    {
        size_t sizeNumeric = storage.size();
        char sizeBinary[sizeof(sizeNumeric)];
        strncpy(sizeBinary, (char *)&sizeNumeric, sizeof(sizeNumeric));

        output.write(sizeBinary, sizeof(sizeNumeric));
        for (uint16_t i = 0; i < sizeNumeric; i++)
            if (!binWriteMember(output, storage.at(i)))
                std::cerr << COLORS::fgBrightRed << "Error at write Member #" << i + 1 << "!\n";
    }
    else
        std::cerr << COLORS::fgBrightRed << "File " << file << " not exist or corrupt"<< COLORS::reset << "\n";

    output.close();
}

void txtOutput(std::string file, std::vector<Member> str)
{
    std::ofstream txtOut(file);
    if (txtOut.good())
    {
        for (size_t i = 0; i < str.size(); i++)
            txtOut << "Member #" << i + 1 << "\n" << str.at(i) << "\n\n";
    }
    else
        std::cerr << COLORS::fgBrightRed << "File " << file << " not exist or corrupt"<< COLORS::reset << "\n";

    txtOut.close();
}

void finalAct(std::vector<Member> &storage, const char *text)
{
    print(storage, text);
    std::string file;
    std::cout << "Enter name file[.txt] for output current members: ";
    std::cin >> file;
    txtOutput(file, storage);
}

bool isEmpty(std::vector<Member> str,int act)
{
    bool result = str.empty();
    if (result)
        std::cerr << COLORS::fgBrightRed << "Action " << act << " not accessed: array members is empty.\n"<< COLORS::reset << "\n";
    return result;
}