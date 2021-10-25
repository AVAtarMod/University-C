#ifndef FUNCTIONS_LIB
#define FUNCTIONS_LIB

#include <iostream>

int getRandomNumber(int from, int to);

// String functions
// TODO move to string library
void replace(char *string, int *indexes, int lengthIndexes, char symbol);
int *indexSymbols(char *string, char symbol, int &count);

template <class T>
T pow(T a, uint power)
{
    if (power == 0)
        return 1;
    long result = a;
    while (power != 1)
    {
        result *= a;
        --power;
    }
    return result;
}

int getNumberDigits(int number);

#endif //FUNCTIONS_LIB
