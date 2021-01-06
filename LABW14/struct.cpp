#include <iostream>
#include <fstream>
#include <locale>

#include "struct.h"

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

std::istream &operator>>(std::istream &input, Member &member)
{
    setlocale(LC_ALL, "ru_RU.UTF8");

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
    setlocale(LC_ALL, "");
    std::cout << member.fullName << " " << member.age << "y.o"
              << "\nCountry, city: " << member.country << "," << member.city << "\nWork place: " << member.work
              << "\nPhone number: " << member.phoneNumber << "\n";
    return output;
}
