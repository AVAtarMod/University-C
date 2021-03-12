#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>

#include "extension/useful.h"

void getHelp();

int main(int argc, char const *argv[])
{
    if (argc == 2)
    {
        std::ifstream in(argv[1]);
        if (!in.good())
        {
            std::cerr << fgRed << "File corrupt or not exist\n"
                      << reset << getHelp;
            return 1;
        }

        readFile(argv[1]);
    }

    return 0;
}

std::vector<std::vector<int>> readFile(const char *file)
{
    std::ifstream in(file);
    std::vector<std::vector<int>> array;
    array.reserve(1);
    int number, i = 0;
    while (!in.eof())
    {
        char[]
    }

    return array;
}

void getHelp()
{
    std::cout << "Using: task2.app [path/to/filename] - read array from filename\n    Example task2.app files/t2ex.txt\n\n";
}