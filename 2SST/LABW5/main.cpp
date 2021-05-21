#include <iostream>

#include "Labyrinth.hpp"

int main()
{
    Labyrinth test("files/fileldn1.txt");
    std::cout << test.shortestWay();
    return 0;
}
