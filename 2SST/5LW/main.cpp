#include <iostream>

#include "Labyrinth.hpp"

int main()
{
    Labyrinth test("/home/grigory/Programming/C++/Laboratory/2SST/LABW5/files/fieldn1.txt");
    test.show();
    std::cout << test.shortestWay();
    return 0;
}
