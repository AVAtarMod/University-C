#include "functions.h"
#include <ctime>
#include <random>

void getRangeUser(int ln, int* range)
{

    bool correctInput = false;
    while (!correctInput) {
        cout << "Введите границы А,Б : ";
        std::cin >> range[0] >> range[1];

        if (range[0] <= ln && range[1] <= ln && range[0] >= 0 && range[1] >= 0) {
            correctInput = true;
            if (range[0] > range[1]) {
                int temp = range[0];
                range[0] = range[1];
                range[1] = temp;
            }
        } else {
            cout << "Необходимо ввести значения от 0 до " << ln << "\n";
            std::cin.ignore(INT16_MAX, '\n');
            std::cin.clear();
        }
    }
}

int* elementsRelevantConditions(const int* array, int numberElements, bool condition(int number), int offset)
{

    int* arrayResult = new int[numberElements]();

    for (int i = offset, iRes = offset; i < numberElements; i++) {
        if (condition(array[i])) {
            arrayResult[iRes] = array[i];
            arrayResult[0] = iRes;
            iRes++;
        }
    }

    if (arrayResult[0] == 0) {
        delete[] arrayResult;
        return nullptr;
    } else
        return arrayResult;
}

int* indexesRelevantConditions(const int* ar, int ln, bool condition(int), int offset)
{
    int* arrayResult = new int[ln]();

    for (int i = offset, iRes = offset; i < ln; i++) {
        if (condition(ar[i])) {
            arrayResult[iRes] = i - offset;
            arrayResult[0] = iRes;
            iRes++;
        }
    }

    if (arrayResult[0] == 0) {
        delete[] arrayResult;
        return nullptr;
    } else
        return arrayResult;
}

int indexRelevantConditions(const int* ar, int ln, bool condition(int), int offset)
{
    int result = -1;

    for (int i = offset; i < ln; i++) {
        if (condition(ar[i])) {
            result = i - offset;
        }
    }

    return result;
}

int productElements(int* array, int ln, int offset)
{
    int result = 1;
    for (int i = offset; i < ln; i++) {
        result *= array[i];
    }

    if (ln - offset == 0)
        return -1;
    else
        return result;
}

//Вывод количества элементов выводится в 1 элемент массива (с индексом 0)
int* generationArray()
{
    std::default_random_engine engine(static_cast<long unsigned>(time(nullptr)));
    std::uniform_int_distribution<int> random(-25, 25);

    int* array = new int[11];

    array[0] = 11;
    for (int i = 1; i < 12; i++) {
        array[i] = random(engine);
    }

    return array;
}

//Вывод количества элементов выводится в 1 элемент массива (с индексом 0,поэтому происходит смещение на +1)
int* generationAndPrintArray(std::string text, int offset)
{
    int* array = generationArray();
    int numberElements = *array;
    printArray(array, numberElements, text, offset, true);
    return array;
}

bool isSimple(int number)
{
    int counter = 0;

    for (int divider = 2; divider <= number; divider++) {
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

bool isEndsIn3(int number)
{
    return (abs(number) % 10 == 3);
}