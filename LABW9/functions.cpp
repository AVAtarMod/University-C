#include <random>
#include <ctime>
#include "functions.h"

int *elementsRelevantConditions(const int *array, int numberElements, bool condition(int number), int offset)
{

    int *arrayResult = new int[numberElements]();

    for (int i = offset, iRes = offset; i < numberElements; i++)
    {
        if (condition(array[i]))
        {
            arrayResult[iRes] = array[i];
            arrayResult[0] = iRes;
            iRes++;
        }
    }

    if (arrayResult[0] == 0)
        return nullptr;
    else
        return arrayResult;
}

int *indexesRelevantConditions(const int *ar, int ln, bool condition(int),int offset)
{
    int *arrayResult = new int[ln]();

    for (int i = offset, iRes = offset; i < ln; i++)
    {
        if (condition(ar[i]))
        {
            arrayResult[iRes] = i-offset;
            arrayResult[0] = iRes;
            iRes++;
        }
    }

    if (arrayResult[0] == 0)
        return nullptr;
    else
        return arrayResult;
}

int indexRelevantConditions(const int *ar, int ln, bool condition(int),int offset)
{
    int result = -1;

    for (int i = offset; i < ln; i++)
    {
        if (condition(ar[i]))
        {
            result = i-offset;
        }
    }

    return result;
}

//Вывод количества элементов выводится в 1 элемент массива (с индексом 0)
int *generationArray()
{
    std::default_random_engine engine(static_cast<long unsigned>(time(nullptr)));
    std::uniform_int_distribution<int> random(-25, 25);

    int *array = new int[11];
    int numberElements = 10;

    array[0] = numberElements + 1;
    for (int i = 1; i <= numberElements; i++)
    {
        array[i] = random(engine);
    }

    return array;
}

//Вывод количества элементов выводится в 1 элемент массива (с индексом 0,поэтому происходит смещение на +1)
int *generationAndPrintArray(std::string text, int offset)
{
    int *array = generationArray();
    int numberElements = *array;
    printArray(array, numberElements, text, offset, true);
    return array;
}

bool isSimple(int number)
{
    int counter = 0;

    for (int divider = 2; divider <= number; divider++)
    {
        if (number % divider == 0)
            counter++;
    }
    if (counter == 1)
        return true;
    else
        return false;
}

bool isDivideBy3(int number)
{
    return (number % 3 == 0);
}

bool isNegative(int number)
{
    return (number < 0);
}

bool isDivideBy7(int number)
{
    return (number % 7 == 0 && number != 0);
}