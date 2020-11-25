#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "functions.cpp"

int task1();
int task2();
int task3();
int task4();
int task5();
int task6();
int task7();
int task8();
int task9();

int *generationArray();
int *generationAndPrintArray(std::string text, bool);

template<class Type>
void deleteArray(Type*);

template<class Type>
void printArray(Type*, int, std::string text, bool, bool);

#endif //FUNCTIONS_H