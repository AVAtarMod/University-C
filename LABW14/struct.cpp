#include <iostream>
#include <locale>

#include "struct.h"

std::istream &operator>>(std::istream &input, Member &member)
{
    setlocale(LC_ALL,"");
    std::cout << "Enter\n- fullname: ";
    //TODO Add getline impl
    // input.getline(member.fullName);
    std::cout << "\n- country: ";
    input >> member.country;
    std::cout << "\n- city: ";
    input >> member.city;
    std::cout << "\n- work (place): ";
    input >> member.work;
    std::cout << "\n- age: ";
    input >> member.age;
    std::cout << "\n- phone number: ";
    input >> member.phoneNumber;
    return input;
}

std::ostream &operator<<(std::ostream &output, Member &member)
{
    setlocale(LC_ALL,"");
    std::cout << member.fullName << " " << member.age << "y.o"
              << "\nCountry, city: " << member.country << "," << member.city << "\nWork place: " << member.work
              << "\nPhone number: " << member.phoneNumber;
    return output;
}


