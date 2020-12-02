#include "functions.h"

template <class Type>
void deleteArray(Type *array)
{
    delete[] array;
    array = nullptr;
}

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

template <class Type>
void printArray(Type *array, int numberElements, std::string text, bool afterChanging, bool showZero)
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

    if (afterChanging)
        cout << "] (После изменения)\n";
    else
        cout << " ]\n";
}
//Вывод количества элементов выводится в 1 элемент массива (с индексом 0,поэтому происходит смещение на +1)
int *generationAndPrintArray(std::string text, bool afterChanging)
{
    int *array = generationArray();
    int numberElements = *array;
    printArray(array, numberElements, text, afterChanging);
    return array;
}