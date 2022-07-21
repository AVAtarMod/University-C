#include <fstream>
#include <iostream>

#include "files.h"

void printArray(int** array, int rows, int collumns, const char* filename)
{
    std::ofstream out(filename);
    for (int row = 0, printRow = row; row < rows; row++) {
        if (array[row]) {
            for (int coll = 0; coll < collumns; coll++) {
                out << array[row][coll] << " ";
            }
            out << "\n";
            ++printRow;
        }
    }
    out.close();
}

void getFileAdressUser(char* storage, int len)
{
    std::cout << "Please enter filename: ";
    std::cin.getline(storage, len);
}