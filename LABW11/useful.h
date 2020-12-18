#ifndef USEFUL
#define USEFUL

#include <iostream>

template<class T>
T printAndScan(const char* text){
    T data;
    printf("%s",text);
    std::cin >> data;
    std::cin.ignore(32767, '\n');
    std::cin.clear();

    return data;
}

#endif