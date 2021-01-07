#include <iostream>
#include <fstream>
#include <locale>

#include "struct.h"

bool searchText(const char *source, const char *text)
{
    std::string sourceStr{source};
    if (sourceStr.find(text) != sourceStr.npos)
        return true;
    else
        return false;
}

bool binWriteMember(std::ofstream &output, Member &member)
{
    std::unique_ptr<char[]> memberBinary = member;
    output.write(memberBinary.get(), BUFFER_SIZE);
    if (output.good())
        return true;
    else
        return false;
}

bool binReadMember(std::ifstream &input, Member &member)
{
    char buffer[BUFFER_SIZE];
    input.read(buffer, BUFFER_SIZE);
    member = static_cast<Member>(buffer);
    if (input.good())
        return true;
    else
        return false;
}

void editMember(Member &member)
{
    std::cout << member << "\n";
    std::cout << "Avaliable actions:\n\t"
                 "1) Edit fullnamen\n\t"
                 "2) Edit country\n\t"
                 "3) Edit cityn\n\t"
                 "4) Edit work place\n\t"
                 "5) Edit age\n\t"
                 "6) Edit phone number\n\t"
                 "7) Exit\n";
    uint32_t act = 0;
    while (act != 7)
    {
        std::cout << "  Enter action: ";
        std::cin.clear();
        std::cin >> act;
        switch (act)
        {
        case 1:
            std::cout << "  Enter: ";
            std::cin.ignore(INT16_MAX, '\n');
            std::cin.getline(member.fullName, STR_SIZE, '\n');
            break;
        case 2:
            std::cout << "  Enter: ";
            std::cin.ignore(INT16_MAX, '\n');
            std::cin.getline(member.country, STR_SIZE, '\n');
            break;
        case 3:
            std::cout << "  Enter: ";
            std::cin.ignore(INT16_MAX, '\n');
            std::cin.getline(member.city, STR_SIZE, '\n');
            break;
        case 4:
            std::cout << "  Enter: ";
            std::cin.ignore(INT16_MAX, '\n');
            std::cin.getline(member.work, STR_SIZE, '\n');
            break;
        case 5:
            std::cout << "  Enter: ";
            std::cin >> member.age;
            break;
        case 6:
            std::cout << "  Enter: ";
            std::cin >> member.phoneNumber;
            break;
        case 7:
            std::cout << "Exiting...\n";
            break;
        default:
            break;
        }
        std::cout << "  Do you want exit? [7]Yes [1-6]Continue editing.\n";
    }
}

std::istream &operator>>(std::istream &input, Member &member)
{

    input.ignore(INT16_MAX, '\n');
    std::cout << "Enter\n- fullname: ";
    input.getline(member.fullName, STR_SIZE, '\n');
    input.ignore(INT16_MAX, '\n');

    std::cout << "- country: ";
    input.getline(member.country, STR_SIZE, '\n');
    input.ignore(INT16_MAX, '\n');

    std::cout << "- city: ";
    input.getline(member.city, STR_SIZE, '\n');
    input.ignore(INT16_MAX, '\n');

    std::cout << "- work (place): ";
    input.getline(member.work, STR_SIZE, '\n');
    input.ignore(INT16_MAX, '\n');

    std::cout << "- age: ";
    input >> member.age;
    std::cout << "- phone number: ";
    input >> member.phoneNumber;

    return input;
}

std::ostream &operator<<(std::ostream &output, Member &member)
{
    output << member.fullName << " " << member.age << " y.o"
           << "\nCountry, city: " << member.country << ", " << member.city << "\nWork place: " << member.work
           << "\nPhone number: " << member.phoneNumber << "\n";
    return output;
}
