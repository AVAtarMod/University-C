#ifndef ARRAYS1D
#define ARRAYS1D

#include <ctime>
#include <random>
#include <chrono>

/*         Abbreviation:
    ar = array
    ln = number elements (length of array)
    minN = minimal number
    maxN = maximal number
    arRes = array for result

    fsNum = first number
 */

namespace arrays1d
{
    enum sort
    {
        RANDOMLY,
        NOT_DECREASING,
        NOT_INCREASING
    };

    int getLenghtUser();
    int getLenghtRandom(int minN = 5, int maxN = 10);
    int getIndexUser(const int lnArray, const char *reason = "");
    int getElementUser(const char *reason = "");

    int *generateFromUser(int *ar, int ln);

    template <class T, class L>
    void generateRandom(T *array, L numberElements, L minNumber, L maxNumber)
    {
        std::mt19937 engine(static_cast<unsigned long>(clock()));
        std::uniform_int_distribution<int> random(static_cast<int>(minNumber), static_cast<int>(maxNumber));

        for (L i = 0; i < numberElements; i++)
        {
            array[i] = random(engine);
        }
    }

    template <class T>
    void print(const T *array, const unsigned numberElements, const char *text = "", const unsigned offset = 0)
    {
        printf("Значения массива %s : [ ", text);
        for (unsigned i = offset; i < numberElements; i++)
        {
            printf("%d, ", array[i]);
        }
        printf("\b\b ]\n");
    }

    /**
     * @tparam T type of array
     * @tparam L type of length (unsigned types is recommended)
     * @tparam FT (type of gen borders)
     * @param array array
     * @param length length of array
     * @param method see sort enum members
     */
    template <class T, class L, class FT>
    void generate(T *array, L length, sort method, FT from, FT to)
    {
        if (method == RANDOMLY)
        {
            generateRandom(array, length, static_cast<FT>(from), static_cast<FT>(to));
        }
        else
        {
            for (unsigned i = 0; i < length; i++)
            {
                array[i] = static_cast<T>(i);
            }
        }
    }

    int searchElement(const int *ar, const int ln, const int number);
    int searchIndexMinMaxElement(const int *ar, int ln, bool comparator(int, int));
    int searchMinMaxElementWithConditions(const int *ar, int ln, bool comparator(int, int), bool condition(int));

    //Возвращает массив индексов с длиной в 1 элементе.
    int *searchIndexElements(const int *ar, const int ln, const int number);

    int *elementsRelevantConditions(int *ar, int ln, bool condition(int));

    //Возвращает массив с длиной в 1 элементе.
    int *deleteCoincidences(int *ar, int ln, int element);
    int *deleteElement(int *ar, int ln, int index);

    int *pasteElement(int *ar, int ln, int index, int element);

    int computeSumElements(const int *ar, int ln, bool condition(int), int action(int));

    bool isMax(const int a, const int b);
    bool isMin(const int a, const int b);
    bool isOdd(const int number);
    bool isEven(const int number);
    bool isNegative(const int number);
    bool alwaysTrue(const int);

    int doNothing(const int number);
    int doAbs(const int number);
} // namespace arrays1d

int getRandomNumber(int from, int to);

#endif // ARRAYS1D
