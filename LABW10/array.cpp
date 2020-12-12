#include <iostream>
#include <ctime>
#include <random>

#include "array.h"

int getLenghtUser(){
    printf("Введите длину массива: ");
    int length;

    scanf("%d",&length);
    return length;
}

int *generateFromUser(int *array, int numberElements)
{
    printf("Введите элементы массива через пробел: ");

    for (int i = 0; i < numberElements; i++)
    {
        int value;
        scanf("%d", &value);
        array[i] = value;
    }

    return array;
}

int *generateRandom(int *array, int numberElements, int minNumber = -25, int maxNumber = 25)
{
    std::default_random_engine engine(time(nullptr));
    std::uniform_int_distribution<int> random(minNumber, maxNumber);

    for (int i = 0; i < numberElements; i++)
    {
        array[i] = random(engine);
    }

    return array;
}

int searchElement(const int *array, const int numberElements, const int number)
{
    for (int i = 0; i < numberElements; i++)
    {
        if (*array == number)
            return i + 1;
        array++;
    }
    return -1;
}

int searchMinMaxElement(const int *array, int numberElements, bool *comparator(int firstNumber, int secondNumber))
{
    int firstNumber = *array;
    int result;

    for (int i = 1; i < numberElements; i++)
    {
        array++;
        int secondNumber = *array;
        if (comparator(firstNumber, secondNumber))
            firstNumber = secondNumber;
        result = i + 1;
    }
    return result;
}

int searchMinMaxElementWithConditions(const int *array, int numberElements, bool *comparator(int firstNumber, int secondNumber), bool *condition(int number))
{
    int firstNumber = *array;
    int result;

    for (int i = 1; i < numberElements; i++)
    {
        array++;
        int secondNumber = *array;
        if (comparator(firstNumber, secondNumber) && condition(secondNumber))
            firstNumber = secondNumber;
        result = i + 1;
    }
    return result;
}

int *searchElements(const int *array, int *arrayResult, const int numberElements, const int number)
{
    for (int counterArray = 0, iteratorResult = 1; counterArray < numberElements; counterArray++)
    {
        if (*array == number)
        {
            arrayResult[iteratorResult] = counterArray;
            arrayResult[0] = iteratorResult;
            iteratorResult++;
        }
        array++;
    }
    if (arrayResult[0] == -1)
        return nullptr;
    else
        return arrayResult;
}

int *elementsAppropriateConditions(int *array, int *arrayResult, int numberElements, bool *condition(int number))
{
    for (int counterArray = 0, iteratorResult = 1; counterArray < numberElements; counterArray++)
    {
        if (condition(*array))
        {
            arrayResult[iteratorResult] = *array;
            arrayResult[0] = iteratorResult;
            iteratorResult++;
        }
        array++;
    }

    if (arrayResult[0] == -1)
        return nullptr;
    else
        return arrayResult;
}

int *deleteElement(int *array, int *arrayResult, int numberElements, int index)
{
    for (int counterArray = 0, iteratorResult = 0; counterArray < numberElements; counterArray++)
    {
        if (counterArray != index)
        {
            arrayResult[iteratorResult] = *array;
            iteratorResult++;
        }
        array++;
    }

    return arrayResult;
}

int *deleteCoincidences(int *array, int *arrayResult, int numberElements, int element)
{
    for (int counterArray = 0, iteratorResult = 0; counterArray < numberElements; counterArray++)
    {
        if (*array != element)
        {
            arrayResult[iteratorResult] = *array;
            iteratorResult++;
        }
        array++;
    }

    return arrayResult;
}

int *pasteElement(int *array, int *arrayResult, int numberElements, int index, int element)
{
    for (int counterArray = 0, iteratorResult = 0; counterArray < numberElements; counterArray++)
    {
        if (counterArray == index)
        {
            arrayResult[iteratorResult] = element;
            iteratorResult++;
        }
        arrayResult[iteratorResult] = *array;
        iteratorResult++;
        array++;
    }

    return arrayResult;
}

void print(const int *array, const int numberElements)
{
    printf("Значения массива: [ ");
    for (int i = 0; i < numberElements; i++)
    {
        printf("%d, ", *array);
        array++;
    }
    printf("\b\b ]\n");
}

bool isMax(const int a, const int b)
{
    return (a < b);
}

bool isMin(const int a, const int b)
{
    return (a > b);
}

bool isOdd(const int number)
{
    return (number % 2 == 1);
}

bool isEven(const int number)
{
    return (number % 2 == 0);
}