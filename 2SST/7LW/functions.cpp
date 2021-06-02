#include "functions.hpp"
#include <vector>
#include <iostream>

bool isFileExist(const char *file)
{
    bool exist = false;

    std::ifstream in(file);
    if (in.good())
    {
        exist = true;
    }
    in.close();

    return exist;
}

bool isMagickSquareSolved(int **square, int size)
{
    const int numberRows = size, numberCols = size, numberDiagonals = 2;
    const int numberObjects = numberRows + numberCols + numberDiagonals;
    int sum[numberObjects]{0};

    for (int i = 0; i < numberCols; ++i)
        for (int ii = 0; ii < numberRows; ++ii)
            sum[i] += square[ii][i];

    for (int i = 0; i < numberRows; ++i)
        for (int ii = 0; ii < numberCols; ++ii)
            sum[i + numberCols] += square[i][ii];

    for (int i = 0; i < numberCols; ++i)
        for (int ii = 0; ii < numberRows; ++ii)
            sum[i + numberCols + numberRows] += square[i][i];

    for (int i = 0; i < numberObjects; ++i)
        if (sum[i] != sum[0])
            return false;

    return true;
}

int **magickSquare(unsigned size = 3)
{
    try
    {
        if (size < 2)
            throw "magickSquare: too little size (" + std::to_string(size) + ")";
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    int **square = array2d::init(size, size);

    int counter = 1;
    for (int row = 0; row < size; ++row)
        for (int col = 0; col < size; ++col, ++counter)
            square[row][col] = counter;

    const int row = 0, col = 0;
    while (!isMagickSquareSolved(square, size))
    {
        if ()
    }
    return square;
}