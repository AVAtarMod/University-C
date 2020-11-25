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
    for (int i = 1, negative = 1; i <= numberElements; i++, negative *= -1)
    {
        array[i] = (hqrandom::engine() % 25) * negative;
    }

    return array;
}

template <class Type>
void printArray(Type *array, int numberElements, const char *nameArray, bool afterChanging = false, bool showZero = true)
{
    array++;
    cout << "Массив " << *nameArray << " состоит из [ ";

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

int *generationAndPrintArray(const char *nameArray, bool afterChanging = false)
{
    int *array = generationArray();
    int numberElements = *array;
    printArray(array, numberElements, nameArray, afterChanging);
    return array;
}