#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "functions.cpp"

int task1();
int task2();
int task3();
int task4();
int task5();

int *generationArray();
int *generationAndPrintArray(const char *, bool);

template<class Type>
void deleteArray(Type*);

template<class Type>
void printArray(Type*, int, const char*, bool, bool);

#endif //FUNCTIONS_H