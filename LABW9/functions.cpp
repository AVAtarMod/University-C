#include <iostream>
#include "random.cpp"
using std::cout;
using std::endl;

template <class Type>
void deleteArray(Type *array)
{
    delete[] array;
    array = nullptr;
}

//Вывод количества элементов выводится в 1 элемент массива (с индексом 0)
int *generationArray()
{
    printf("\nВведите число элементов массива: ");
    int numberElements;
    scanf("%d", &numberElements);

    int *array = new int[numberElements + 1];
    array[0] = numberElements + 1;
    for (int i = 1; i <= numberElements; i++)
    {
        array[i] = hqrandom::engine() % 25;
    }

    return array;
}

template <class Type>
void printArray(Type *array, int numberElements, std::string text, bool afterChanging = false, bool showZero = true)
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
int *generationAndPrintArray(std::string text, bool afterChanging = false)
{
    int *array = generationArray();
    int numberElements = *array;
    printArray(array, numberElements, text, afterChanging);
    return array;
}