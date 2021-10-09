#ifndef FUNCTIONS_LIB
#define FUNCTIONS_LIB

#include <iostream>

int getRandomNumber(int from, int to);

// String functions
// TODO move to string library
void replace(char *string, int *indexes, int lengthIndexes, char symbol);
int *indexSymbols(char *string, char symbol, int &count);

template <class T>
T pow(T a, int power)
{
    if (power == 1)
        return a;
    else
        return pow(a * a, power - 1);
}

#endif //FUNCTIONS_LIB