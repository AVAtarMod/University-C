#ifndef ARRAYS_2D
#define ARRAYS_2D

namespace array2d
{
    int *getRangeUser();
    int *getSizeUser();

    //Генерирует пару чисел от А до В;
    int *getRangeRandom(int A, int B);

    int **init(const int rows, const int collumns);
    void fill(int **array, const int rows, const int collumns);
    void fillUser(int **array, const int rows, const int collumns, const char *text = "");

    int searchSortRows(int **array, int rows, int collumns, bool condition(int, int));

    void print(int **array, int rows, int collumns, const char *text = "", int maxElement = 0, int *highlight = nullptr, std::string highlightColor = "");
    void print(int **array, int rows, int collumns, const char *text, int maxElement, int *highlight, int highlightSize, std::string highlightColor);

    void printCollumn(int **array, const int rows, const int collumn, const char *text = "");
    void invertRows(int ***array, int rows, bool fast = true, int collumns = 0);
    void checkWork(int **array, int *size, int *range, const char *text = "");
    void copy(int **source, int rows, int collumns, int **destination);
    void delete_(int **array, int rows);
    void getCollumn(int **array, int rows, int *result, int collumn = 0);
    void rebalance(int ***array, int rows, int collumns, int &newCollumns);

    int *compare(int **arrayA, int **arrayB, int rowsMin, int collumnsMin, bool comparator(int, int, int &));

    bool isEqualElements(int elFrom1Ar, int elFrom2Ar, int &result);

} // namespace array2d

int getRandomNumber(int from, int to);
int numDigits(int number);
#endif