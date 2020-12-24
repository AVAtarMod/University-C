#ifndef ARRAYS_2D
#define ARRAYS_2D

namespace array2d
{
    int *getRangeUser();
    int *getSizeUser();

    //Генерирует пару чисел от А до В;
    int *getRangeRandom(int A, int B);

    int **init(const int rows, const int collumns);
    int **fillRandom(int **array, int leftLim, int rightLim, const int rows, const int collumns);

    int searchSortRows(int **array, int rows, int collumns, bool condition(int, int));

    void print(int **array, int rows, int collumns, const char *text = "", int maxElement = 0);
    void printCollumn(int **array, const int rows, const int collumn, const char *text = "");
    void checkWork(int **array, int *size, int *range);
    int **copy(int **array, int rows, int collumns);
    void delete_(int **array, int rows);
    void getCollumn(int **array, int rows, int *result, int collumn = 0);

    int *compare(int **arrayA, int **arrayB, int rowsMin, int collumnsMin, bool comparator(int, int, int &));

    bool isEqualElements(int elFrom1Ar, int elFrom2Ar, int &result);

} // namespace array2d

int getRandomNumber();
int numDigits(int number);
#endif