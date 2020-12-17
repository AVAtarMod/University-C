#ifndef ARRAYS1D
#define ARRAYS1D

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
    int getLenghtUser();
    int getLenghtRandom(int minN = 5, int maxN = 10);
    int getIndexUser(const int lnArray, const char *reason = "");
    int getElementUser(const char *reason = "");

    int *generateFromUser(int *ar, int ln);
    int *generateRandom(int *ar, int ln, int minN = -25, int maxN = 25);
    void print(const int *ar, const int ln, const char *text = "", const int offset = 0);

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
    bool alwaysTrue(const int);

    int doNothing(const int number);
    int doAbs(const int number);
} // namespace arrays1d

#endif // ARRAYS1D
