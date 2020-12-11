// #ifndef FUNCTIONS
// #define FUNCTIONS

#include <iostream>
#include <random>
using std::cout;
using std::endl;
using std::string;

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
int *generationAndPrintArray(string text);

template <class Type>
void deleteArray(Type **array)
{
    delete[] *array;
    *array = nullptr;
}

template <class Type>
void printArray(Type *array, int numberElements, std::string text,bool showZero = true)
{
    array++;
    cout << "Массив " << text << " состоит из [ ";

    for (short int i = 1; i < numberElements; i++, array++)
    {
        if (*array || showZero)
        {
            cout << *array;
            if (i != numberElements - 1)
            {
                cout << ";";
            }
        }
    }
    cout << "\n";
}
// #endif //FUNCTIONS