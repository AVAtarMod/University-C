#include <iostream>

#include "algorithms.hpp"
#include "useful.hpp"

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL,"ru_RU.UTF8");
    if (argc == 3)
        std::cout << boyerMoor(argv[2]) << linear(argv[1], argv[2]) << std::endl;
    else
    {
        std::cerr << fgBrightRed
                  << "[error] You did't enter strings or your input incorrect\n"
                  << reset;
        std::cout << "Enter 2 words: ";
        std::string f, s;
        std::cin >> f >> s;
        std::cout << linearAccelerated(f.c_str(), s.c_str()) << linear(f.c_str(), s.c_str()) << std::endl;
    }
    return 0;
}
