#ifndef ARRAYS1D
#define ARRAYS1D

#include <random>
#include <iostream>
#include <ctime>
#include <algorithm>

/*  Abbreviations:
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
        NOT_INCREASING,
        NOT_DECREASING,
        RANDOMLY
    };

    int getLenghtUser();
    int getLenghtRandom(int minN = 5, int maxN = 10);
    int getIndexUser(const int lnArray, const char *reason = "");
    int getElementUser(const char *reason = "");

    void generateFromUser(int *ar, int ln);

    template <class T>
    void generateRandom(T *array, uint32_t numberElements, uint32_t minNumber, uint32_t maxNumber)
    {
        srand(clock());
        
        for (uint32_t i = 0; i < numberElements; i++)
            array[i] = random()%maxNumber + minNumber;
        
        std::vector<T> container;
        container.resize(numberElements);
        for (uint32_t i = 0; i < numberElements; i++)
            container.at(i) = array[i];

        while (std::is_sorted(container.begin(), container.end()))
        {
            generateRandom(array, numberElements, minNumber, maxNumber);
        }
    }

    template <class T>
    void print(const T *array, const uint32_t numberElements, const char *text = "", const uint32_t offset = 0)
    {
        std::cout << "Значения массива " << text << " : [ ";
        for (uint32_t i = offset; i < numberElements; i++)
            std::cout << array[i] << ", ";
        std::cout << "\b\b ]\n";
    }
    /**
     * @brief Generating array
     * 
     * @param ln length array
     * @param element sotring order
     * @param from for RANDOMLY order
     * @param to for RANDOMLY order
     */
    void generate(int *array, uint32_t ln, sort element, uint32_t from = 0, uint32_t to = 0);

    int searchIndexElement(const int *ar, const int ln, const int number);
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

#endif // ARRAYS1D

int randomNumber(int from, int to);