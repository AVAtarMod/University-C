#ifndef FUNCTIONS
#define FUNCTIONS

#include <iostream>
using std::string;
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
int *generationAndPrintArray(string text, int offset);
int *elementsRelevantConditions(const int *ar, int ln, bool condition(int),int offset = 0);
int *indexesRelevantConditions(const int *ar, int ln, bool condition(int),int offset = 0);
int indexRelevantConditions(const int *ar, int ln, bool condition(int),int offset = 0);


template <class Type>
void deleteArray(Type *array)
{
    delete[] array;
}

template <class Type>
void printArray(Type *array, int numberElements, std::string text,int offset=0, bool showZero = true)
{
    cout << "Массив " << text << " состоит из [ ";

    for (short int i = offset; i < numberElements; i++)
    {
        if (array[i] || showZero)
        {
            cout << array[i];
            if (i != numberElements - 1)
            {
                cout << ";";
            }
        }
    }
    cout << " ]\n";
}

bool isSimple(int number);
bool isDivideBy3(int number);
bool isNegative(int number);
bool isDivideBy7(int number);

#endif //FUNCTIONS