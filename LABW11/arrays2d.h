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

    int isSortRow(int **array, int rows, int collumns, bool condition(int, int));

    void print(int **array, int rows, int collumns, const char *text = "", int maxElement = 0);
    void checkWork(int **array,int *size, int *range);
    int **copy(int **array, int rows, int collumns);
    void delete_(int **array, int rows);

} // namespace array2d
int getRandomNumber(int leftLim, int rightLim);
int numDigits(int number);
#endif