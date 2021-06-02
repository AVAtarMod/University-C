#ifndef ARRAYS_2D
#define ARRAYS_2D

namespace array2d
{
    int *getRangeUser();
    int *getSizeUser();

    int *getRangeRandom(int from, int to);
    int *getSizeRandom();

    int **init(const int rows, const int collumns);
    void fillRandom(int **array, int numbersFrom, int numbersTo, const int rows, const int collumns);
    void fillUser(int **array, const int rows, const int collumns, const char *text = "");

    int searchSortRows(int **array, int rows, int collumns, bool condition(int, int));

    void printCollumn(int **array, const int rows, const int collumn, const char *text = "");
    void invertRows(int ***array, int rows, bool fast = true, int collumns = 0);
    void copy(int **source, int rows, int collumns, int **destination);
    void delete_(int **array, int rows);
    void getCollumn(int **array, int rows, int *result, int collumn = 0);
    void rebalance(int ***array, int rows, int collumns, int &newCollumns);

    int *compare(int **arrayA, int **arrayB, int rowsMin, int collumnsMin, bool comparator(int, int, int &));

    bool isEqualElements(int elFrom1Ar, int elFrom2Ar, int &result);

} // namespace array2d

int getRandomNumber(int from,int to);
int numDigits(int number);
#endif