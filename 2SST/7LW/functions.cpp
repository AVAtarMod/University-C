#include "functions.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

bool isMagickSquareSolved(unsigned **square, unsigned size)
{
    const unsigned numberRows = size, numberCols = size, numberDiagonals = 2;
    const unsigned numberObjects = numberRows + numberCols + numberDiagonals;

    unsigned *sum = new unsigned[numberObjects]{0};

    for (unsigned i = 0; i < numberCols; ++i)
        for (unsigned ii = 0; ii < numberRows; ++ii)
            sum[i] += square[ii][i];

    for (unsigned i = 0; i < numberRows; ++i)
        for (unsigned ii = 0; ii < numberCols; ++ii)
            sum[i + numberCols] += square[i][ii];

    for (unsigned i = 0; i < numberCols; ++i)
        sum[numberCols + numberRows] += square[i][i];

    for (unsigned i = size - 1, ii; i < 0 - 1; --i, ++ii)
        sum[numberCols + numberCols + 1] += square[i][ii];

    bool solved = true;
    for (unsigned i = 0; i < numberObjects && solved; ++i)
        if (sum[i] != sum[0])
            solved = false;

    delete[] sum;
    return solved;
}

bool checkNumber(unsigned number)
{
    int tnum = number, c = 0;
    while (tnum != 0)
    {
        int temp = tnum % 10;
        if (temp == 0)
            return false;
        tnum /= 10;
        c++;
    }
    int p = 0;
    tnum = number;
    for (int i = 0; i < c; ++i)
    {
        int temp1 = tnum % 10;
        int tnum2 = number;
        int p2 = 0;
        while (tnum2 != 0)
        {
            int temp = tnum2 % 10;
            if (temp == temp1 && p != p2)
                return false;
            tnum2 /= 10;
            p2++;
        }
        p++;

        tnum /= 10;
    }

    return true;
}

unsigned **magickSquare(unsigned size)
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

    unsigned **square = array2d::init<unsigned>(size, size, 0);

    unsigned counter = 1;
    for (unsigned row = 0; row < size; ++row)
        for (unsigned col = 0; col < size; ++col, ++counter)
            square[row][col] = counter;

    unsigned start = 123456789;
    while (start < 987654321)
    {
        unsigned ts = start;
        for (unsigned row = size - 1; row < 0 - 1; --row)
            for (unsigned col = size - 1; col < 0 - 1; --col)
            {
                square[row][col] = ts % 10;
                ts /= 10;
            }
        if (isMagickSquareSolved(square, size))
        {
            for (int i = 0; i < 3; ++i)
            {
                for (int ii = 0; ii < 3; ++ii)
                {
                    std::cout << square[i][ii] << " ";
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }
        start++;
        while (!checkNumber(start))
        {
            start++;
        }
    }
    return square;
}

struct setNumbers
{
    int a, b;
    bool used = false;

    setNumbers(int a = 0, int b = 0, bool used = false)
    {
        this->a = a;
        this->b = b;
        this->used = used;
    }
    bool operator==(setNumbers &b)
    {
        return (this->a == b.a && this->b == b.b);
    }
};

bool compareNumbers(int a, int b, int operatorChar)
{
    if (operatorChar == '<')
        return a < b;
    else
        return a > b;
}

void solveBoxesProblem(int *array, unsigned length)
{
    const unsigned amountNumbers = length / 2 + 1;
    const unsigned amountOperators = amountNumbers - 1;
    int *numbers = new int[amountNumbers];
    int *operators = new int[amountOperators];

    for (unsigned i = 0; i < amountNumbers; ++i)
        numbers[i] = array[i];

    for (unsigned i = 0; i < amountOperators; ++i)
        operators[i] = array[i + amountNumbers];

    std::vector<std::vector<setNumbers>> sets;
    sets.resize(amountOperators);
    for (unsigned i = 0; i < amountOperators; ++i)
    {
        for (unsigned a = 0; a < amountNumbers; ++a)
            for (unsigned b = 0; b < amountNumbers; ++b)
            {
                setNumbers current = {numbers[a], numbers[b]};
                bool uniqueSet = (std::find_if(sets[i].begin(), sets[i].end(), [&current](setNumbers &a) { return (current.a == a.a && current.b == a.b); }) == sets[i].end());
                if (compareNumbers(numbers[a], numbers[b], operators[i]) && uniqueSet)
                {
                    sets.at(i).push_back(current);
                }
            }
    }
}