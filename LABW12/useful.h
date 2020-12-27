#ifndef USEFUL
#define USEFUL

#include <iostream>

template<class T>
T printAndScan(const char* text){
    T data;
    std::cout << text;
    std::cin >> data;
    std::cin.ignore(32767, '\n');

    return data;
}

#endif