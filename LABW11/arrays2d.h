#ifndef ARRAYS_2D
#define ARRAYS_2D

namespace array2d
{

    int *getRangeUser();

    int **init(const int rows, const int collumns);
    int **fillRandom(int **array, int leftLim, int rightLim, const int rows, const int collumns);

    void print(int **array, const int collumns, const int rows, const char *text = "", int maxElement = 0);

    int numDigits(int number);

} // namespace array2d

#endif