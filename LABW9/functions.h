#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "functions.cpp"

int *generationArray();
void printArray(int *, int, const char *, bool);

int *generationAndPrintArray(const char *, bool);
void deleteArray(int *);

#endif //FUNCTIONS_H