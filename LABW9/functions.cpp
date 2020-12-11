#include "functions.h"

//Вывод количества элементов выводится в 1 элемент массива (с индексом 0)
int *generationArray()
{
    std::default_random_engine engine(time(nullptr));
    std::uniform_int_distribution<int> random(-25,25);

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
int *generationAndPrintArray(std::string text)
{
    int *array = generationArray();
    int numberElements = *array;
    printArray(array, numberElements, text, true);
    return array;
}