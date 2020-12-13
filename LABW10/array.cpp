#include <iostream>
#include <ctime>
#include <random>

#include "array.h"

int getLenghtUser()
{
    printf("Введите длину массива: ");
    int length;

    scanf("%d", &length);
    return length;
}

int getLenghtRandom(int minN, int maxN)
{
    try
    {
        if (minN < 0)
            throw minN;
    }
    catch (int minN)
    {
        std::cerr << "ОШИБКА(minN =" << minN << "):minN должен быть > 0. ";
    }

    std::mt19937 engine(static_cast<unsigned long>(clock()));
    std::uniform_int_distribution<int> random(minN, maxN);
    return random(engine);
}

int getIndexUser(const int numberElementsArray, const char *reason)
{
    printf("Введите индекс (%s): ", reason);
    int index;
    scanf("%d", &index);
    while (true)
    {
        if (index < 0 && index > numberElementsArray)
        {
            printf("Введен некорректный индекс. Он должен быть числом от 0 до %d", numberElementsArray);
        }
        else
            return index;
    }
}

int getElementUser(const char *reason){
    int element;
    printf("Введите элемент (%s): ",reason);
    scanf("%d",&element);
    
    return element;
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

int *generateRandom(int *array, int numberElements, int minNumber, int maxNumber)
{
    std::mt19937 engine(static_cast<unsigned long>(clock()));
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
        if (array[i] == number)
            return i;
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

int* pasteElement(int *array, int numberElements, int index, int element)
{
    int* arrayResult = new int[numberElements+1];
    //i = iterator
    for (int i = 0, iRes = 0; i < numberElements; i++)
    {
        if (i == index)
        {
            arrayResult[iRes] = element;
            iRes++;
        }
        arrayResult[iRes] = *array;
        iRes++;
        array++;
    }

    return arrayResult;
}

void print(const int *array, const int numberElements)
{
    printf("Значения массива : [ ");
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