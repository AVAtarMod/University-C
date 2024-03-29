#include <iostream>

#include "arrays1d.hpp"

namespace arrays1d
{
    int getLenghtUser()
    {
        printf("Введите длину массива: ");
        int length;

        scanf("%d", &length);
        std::cin.ignore(INT16_MAX, '\n');

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
                std::cin.ignore(INT16_MAX, '\n');
                return index;
            }
        }
    }

    int getElementUser(const char *reason)
    {
        int element;

        printf("Введите элемент (%s): ", reason);
        scanf("%d", &element);
        std::cin.ignore(INT16_MAX, '\n');

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
        std::cin.ignore(INT16_MAX, '\n');
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

    int searchIndexMinMaxElement(const int *array, int numberElements, bool comparator(int, int))
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

    int searchMinMaxElementWithConditions(const int *array, int numberElements, bool comparator(int, int), bool condition(int))
    {
        int firstNumber = *array;
        int result = 0;

        for (int i = 1; i < numberElements; i++)
        {
            array++;
            int secondNumber = *array;
            if (comparator(firstNumber, secondNumber))
            {
                if (condition(secondNumber))
                {
                    firstNumber = secondNumber;
                    result = i;
                }
            }
        }
        return result;
    }

    int *searchIndexElements(const int *array, const int numberElements, const int number)
    {
        int *arrayResult = new int[numberElements];

        for (int i = 0, iRes = 1; i < numberElements; i++)
        {
            if (array[i] == number)
            {
                arrayResult[iRes] = i; //Заполняем arrayResult
                arrayResult[0] = iRes; //Записываем длину массива в 1 элемент
                iRes++;
            }
        }
        if (arrayResult[0] == 0)
            return nullptr;
        else
            return arrayResult;
    }

    int *elementsRelevantConditions(int *array, int numberElements, bool condition(int number))
    {
        int *arrayResult = new int[numberElements];

        for (int i = 0, iRes = 1; i < numberElements; i++)
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

    int *deleteElement(int *array, int numberElements, int index)
    {
        int *arrayResult = new int[numberElements];

        for (int i = 0, iRes = 0; i < numberElements; i++)
        {
            if (i != index)
            {
                arrayResult[iRes] = array[i];
                iRes++;
            }
        }

        delete[] array;

        return arrayResult;
    }

    int *deleteCoincidences(int *array, int numberElements, int element)
    {
        int *arrayResult = new int[numberElements];

        for (int i = 0, iRes = 1; i < numberElements; i++)
        {
            if (array[i] != element)
            {
                arrayResult[iRes] = array[i];
                arrayResult[0] = iRes;
                iRes++;
            }
        }

        delete[] array;

        return arrayResult;
    }

    int *pasteElement(int *array, int numberElements, int index, int element)
    {
        int *arrayResult = new int[numberElements + 1];

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

    int computeSumElements(const int *ar, int ln, bool condition(int), int action(int))
    {
        int sum = 0;

        for (int i = 0; i < ln; i++)
        {
            if (condition(ar[i]))
            {
                sum += action(ar[i]);
            }
        }

        return sum;
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
        return (abs(number % 2) == 1);
    }

    bool isEven(const int number)
    {
        return (abs(number % 2) == 0);
    }

    bool isNegative(const int number)
    {
        return (number < 0);
    }

    bool alwaysTrue(const int)
    {
        return true;
    }

    int doNothing(const int number)
    {
        return number;
    }

    int doAbs(const int number)
    {
        return abs(number);
    }
} // namespace arrays1d

int getRandomNumber(int from, int to)
{
    try
    {
        if (from > to)
            throw "Incorrect couple 'from - to' for generating random numbers";
    }
    catch (const char *message)
    {
        std::cerr << message << '\n';
        exit(1);
    }

    unsigned int now = static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count() % 10000);
    std::mt19937 engine(now);
    std::uniform_int_distribution<int> random(from, to);

    return random(engine);
}