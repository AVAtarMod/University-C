#include <iostream>
#include <fstream>

#include "files.h"

void readArray(int **array, int rows, int collumns, const char *filename)
{
    std::ifstream in(filename);
    for (int row = 0; row < rows; row++)
    {
        for (int coll = 0; coll < collumns; coll++)
        {
            in >> array[row][coll];
        }
    }
    in.close();
}

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