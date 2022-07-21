#include <fstream>
#include <iostream>
#include <vector>

#include "files.h"

void readArray(int** array, int rows, int collumns, const char* filename, const int readPosition)
{
    std::ifstream in(filename);
    in.seekg(readPosition);
    for (int row = 0; row < rows; row++) {
        for (int coll = 0; coll < collumns; coll++) {
            in >> array[row][coll];
        }
    }
    in.close();
}

std::vector<int> readSearchFile(const char* filename)
{
    std::ifstream in(filename);
    std::vector<int> array;
    array.resize(10);
    size_t i = 0;
    for (; !in.eof(); i++) {
        int number;
        in >> number;
        array.at(i) = number;
        if (i % 10 == 9)
            array.resize(array.size() + 10);
    }
    in.close();
    array.resize(i);
    return array;
}

bool isFileExist(const char* file)
{
    bool exist = false;

    std::ifstream in(file);
    if (in.good()) {
        exist = true;
    }
    in.close();

    return exist;
}