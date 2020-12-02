#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <random>
using std::cout;
using std::endl;

int task1();
int task2();
int task3();
int task4();
int task5();
int task6();
int task7();
int task8();
int task9();
int task10();
int task11();

int *generationArray();
int *generationAndPrintArray(std::string text, bool afterChanging = false);

template <class Type>
void deleteArray(Type *array);

template <class Type>
void printArray(Type *array, int numberElements, std::string text, bool afterChanging = false, bool showZero = true);

#endif //FUNCTIONS_H