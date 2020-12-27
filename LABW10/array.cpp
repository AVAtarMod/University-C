#include <iostream>
#include <ctime>
#include <random>

#include "array.h"

int getLenghtUser()
{
    printf("Введите длину массива: ");
    int length;

    scanf("%d", &length);
    std::cin.ignore(32767, '\n');

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
        {
            std::cin.ignore(32767, '\n');
            return index;
        }
    }
}

int getElementUser(const char *reason)
{
    int element;

    printf("Введите элемент (%s): ", reason);
    scanf("%d", &element);
    std::cin.ignore(32767, '\n');

    return element;
}

void generateFromUser(int *array, int numberElements)
{
    printf("Введите элементы массива через пробел: ");

    for (int i = 0; i < numberElements; i++)
    {
        int value;
        scanf("%d", &value);
        array[i] = value;
    }
    std::cin.ignore(32767, '\n');
}

void generateRandom(int *array, int numberElements, int minNumber, int maxNumber)
{
    std::mt19937 engine(static_cast<unsigned long>(clock()));
    std::uniform_int_distribution<int> random(minNumber, maxNumber);

    for (int i = 0; i < numberElements; i++)
    {
        array[i] = random(engine);
    }
}

int indexElement(const int *array, const int numberElements, const int number)
{
    for (int i = 0; i < numberElements; i++)
    {
        if (array[i] == number)
            return i;
    }
    return -1;
}

int indexMinMaxElement(const int *array, int numberElements, bool comparator(int, int))
{
    int firstNumber = *array;
    int result = 0;

    for (int i = 1; i < numberElements; i++)
    {
        if (comparator(firstNumber, array[i]))
        {
            firstNumber = array[i];
            result = i;
        }
    }
    return result;
}

int minMaxElement(const int *array, int numberElements, bool comparator(int, int))
{
    int firstNumber = *array;
    int result = 0;

    for (int i = 1; i < numberElements; i++)
    {
        if (comparator(firstNumber, array[i]))
        {
            firstNumber = array[i];
            result = array[i];
        }
    }
    return result;
}

int indexMinMaxElementWithConditions(const int *array, int numberElements, bool comparator(int, int), bool condition(int))
{
    int result = -1;
    int iFirstNumber = 0;
    for (int i = 1; i < numberElements; i++)
    {
        int secNum = array[i];
        if (condition(array[i]))
        {
            if (comparator(array[iFirstNumber], secNum))
            {
                result = iFirstNumber;
            }
            else
            {
                result = iFirstNumber = i;
            }
        }
    }
    return result;
}

int *searchIndexElements(const int *array, const int numberElements, const int number)
{
    int counter = 0;
    for (int i = 0; i < numberElements; i++)
    {
        if (array[i] == number)
        {
            ++counter;
        }
    }

    int *arrayResult = new int[counter + 1];
    arrayResult[0] = counter + 1;

    for (int i = 0, iRes = 1; i < numberElements; i++)
    {
        if (array[i] == number)
        {
            arrayResult[iRes] = i; //Заполняем arrayResult
            iRes++;
        }
    }
    if (arrayResult[0] == 0)
    {
        delete[] arrayResult;
        return nullptr;
    }
    else
        return arrayResult;
}

int *elementsRelevantConditions(int *array, int numberElements, bool condition(int number))
{
    int *arrayResult = new int[numberElements];

    int lnResult = 1;
    for (int i = 0; i < numberElements; i++)
    {
        if (condition(array[i]))
        {
            arrayResult[lnResult] = array[i];
            arrayResult[0] = lnResult;
            lnResult++;
        }
    }

    if (arrayResult[0] == 0)
    {
        delete[] arrayResult;
        return nullptr;
    }
    else
    {
        int *result = new int[lnResult - 1];
        result[0] = lnResult - 1;
        for (int i = 1; i <= lnResult; i++)
        {
            result[i] = arrayResult[i];
        }
        delete[] arrayResult;

        return result;
    }
}

void deleteElement(int **array, int numberElements, int index, int offset)
{
    int *arrayResult = new int[numberElements - 1];

    for (int i = offset, iRes = 0; i < numberElements; i++)
    {
        if (i != index)
        {
            arrayResult[iRes] = (*array)[i];
            iRes++;
        }
    }

    delete[] * array;
    *array = arrayResult;
}

void deleteElements(int **array, int &numberElements, int element, int offset)
{
    int counter = 0;
    for (int i = offset; i < numberElements; i++)
    {
        if ((*array)[i] != element)
        {
            counter++;
        }
    }

    bool needDelete = (counter >= numberElements - offset) ? false : true;
    if (needDelete)
    {
        numberElements = counter;

        int *arrayResult = new int[counter];

        int iRes = 0;
        for (int i = offset; i < numberElements; i++)
        {
            if ((*array)[i] != element)
            {
                arrayResult[iRes] = (*array)[i];
                iRes++;
            }
        }

        delete[] * array;
        *array = arrayResult;
    }
}

void pasteElement(int **array, int &numberElements, int index, int element)
{
    ++numberElements;
    int *arrayResult = new int[numberElements];

    for (int i = 0, iRes = 0; i < numberElements; i++)
    {
        if (i == index)
        {
            arrayResult[iRes] = element;
            iRes++;
        }
        arrayResult[iRes] = (*array)[i];
        iRes++;
    }

    delete[] * array;
    *array = arrayResult;
}

void print(const int *array, const int numberElements, const char *text, const int offset)
{
    printf("Значения массива %s : [ ", text);
    for (int i = offset; i < numberElements; i++)
    {
        printf("%d, ", array[i]);
    }
    printf("\b\b ]\n");
}

bool isAMax(const int a, const int b)
{
    return (a > b);
}

bool isAMin(const int a, const int b)
{
    return (a < b);
}

bool isOdd(const int number)
{
    return (abs(number % 2) == 1);
}

bool isEven(const int number)
{
    return (abs(number % 2) == 0);
}