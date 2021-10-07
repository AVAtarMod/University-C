#ifndef FUNCTIONS_LIB
#define FUNCTIONS_LIB

#include <iostream>

int getRandomNumber(int from, int to);

// String functions
void replace(char *string, int *indexes, int lengthIndexes, char symbol);
int *indexSymbols(char *string, char symbol, int &count);

#endif //FUNCTIONS_LIB