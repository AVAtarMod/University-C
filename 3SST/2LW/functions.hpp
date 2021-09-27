#ifndef FUNCTIONS_LIB
#define FUNCTIONS_LIB

#include <iostream>

int getRandomNumber(int from, int to);

// String functions
void replace(char *string, int *indexes, int lengthIndexes, char symbol);
int *indexSymbols(char *string, char symbol, int &count);

template<class T>
T printAndScan(const char* text){
    T data;
    std::cout << text;
    std::cin >> data;
    std::cin.ignore(32767, '\n');

    return data;
}

#endif //FUNCTIONS_LIB