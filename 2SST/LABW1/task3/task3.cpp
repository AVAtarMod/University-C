#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>

#include "useful.h"
#include "files.h"
#include "arrays2d.h"

bool helpWasShowed = false;

void getHelp();
void binarySearch(int *storage, int **array, int value, int rows, int cols);
void binarySearch(int *storage, uint16_t storageSize, int *values, uint16_t numberValues, int **array, int rows, int cols);

int main(int argc, char const *argv[])
{
    std::vector<const char *> resultFix(3);
    std::string path;
    while (true)
    {
        bool exit = false;
        bool fileIsDataSearch = false;
        std::vector<int> searchArray;
        if (argc > 1)
        {
            int number;
            if (argc >= 3)
            {
                if (std::string(argv[2]) == "--file" && isFileExist(argv[3]))
                {
                    searchArray = readSearchFile(argv[3]);
                    fileIsDataSearch = true;
                }
                else
                    number = atoi(argv[2]);
            }
            else
            {
                std::cout << "Enter number for search: ";
                std::cin >> number;
            }
            std::ifstream in(argv[1]);

            int cols, rows;
            if (in.good())
            {
                in >> rows >> cols;
                std::string color = fgBrightGreen;

                int **array = array2d::init(rows, cols);
                if (fileIsDataSearch)
                {
                    std::vector<int> arrayResult(searchArray.size() * 2 + 1);
                    readArray(array, rows, cols, argv[1], in.tellg());
                    binarySearch(arrayResult.data(), static_cast<int>(arrayResult.size()), searchArray.data(), static_cast<int>(searchArray.size()), array, rows, cols);
                    array2d::print(array, rows, cols, "", array[rows - 1][cols - 1], arrayResult.data(), arrayResult.size(), color);

                    std::string text("The following numbers were found: " + color);
                    for (size_t i = 0; i < arrayResult.size() - 1; i += 2)
                    {
                        if (arrayResult[i] != -1 && arrayResult[i + 1] != -1)
                            text += std::to_string(array[arrayResult[i]][arrayResult[i + 1]]) + " ";
                    }
                    text += reset + "\n\t" + std::to_string(arrayResult.at(arrayResult.size() - 1)) + " comparisons were produced\n\n";
                    std::cout << text;
                }
                else
                {
                    int *result = new int[3];
                    readArray(array, rows, cols, argv[1], in.tellg());
                    binarySearch(result, array, number, rows, cols);
                    array2d::print(array, rows, cols, "", array[rows - 1][cols - 1], result, color);

                    std::string text = (result[0] == -1) ? std::to_string(number) + " not found! Was produced " + std::to_string(result[2]) + " comparisons\n" : color + std::to_string(number) + reset + " was found at [" + std::to_string(result[0]) + "][" + std::to_string(result[1]) + "]\nWas produced " + std::to_string(result[2]) + " comparisons\n";
                    std::cout << text;

                    delete[] result;
                }
                array2d::delete_(array, rows);
            }
            else
            {
                std::cerr << fgBrightRed << "[error] File corrupt or not exist\n"
                          << reset;
                return 1;
            }
            in.close();
            exit = true;
        }
        else
        {
            std::cerr << fgBrightRed << "[error] You did't enter file path or your input incorrect\n"
                      << reset;
            std::cout << fgBrightYellow << "Enter filepath: ";

            std::cin >> path;
            std::cout << "Enter number for search: ";
            std::string number;
            std::cin >> number;
            std::cout << reset;

            resultFix[0] = "", resultFix[1] = "/home/grigory/Programming/C++/Laboratory/2SST/LABW1/task3/files/t3ex.txt", resultFix[2] = "--file", resultFix[3] = "/home/grigory/Programming/C++/Laboratory/2SST/LABW1/task3/files/t3searchfile.txt";
            // resultFix[0] = "", resultFix[1] = "/home/grigory/Programming/C++/Laboratory/2SST/LABW1/task3/files/t3ex.txt", resultFix[2] = "";
            argc = 4;
            argv = resultFix.data();
            getHelp();
        }
        if (exit)
            return 0;
    }
}

void binarySearch(int *storage, int **array, int value, int rows, int cols)
{
    storage[0] = -1, storage[1] = -1, storage[2] = 0;
    ;
    int left = 0, right = rows * cols;
    bool notFound = true;
    int countComparisons = 0;

    while (left < right && notFound)
    {
        countComparisons++;
        int X = ((left + right) / 2) / rows, Y = ((left + right) / 2) % cols;
        if (array[X][Y] > value)
        {
            right = X * cols + Y;
        }
        else if (array[X][Y] < value)
            left = X * cols + Y + 1;
        else
        {
            notFound = false;
            storage[0] = X, storage[1] = Y;
        }
    }
    storage[2] = countComparisons;
}

void binarySearch(int *storage, uint16_t storageSize, int *values, uint16_t numberValues, int **array, int rows, int cols)
{
    for (uint16_t i = 0; i < storageSize - 1; i++)
    {
        storage[i] = -1;
    }
    storage[storageSize - 1] = 1;

    int countComparisons = 0;
    for (uint16_t i = 0, iStorage = 0; i < numberValues; i++)
    {
        bool notFound = true;
        int value = values[i];
        int left = 0, right = rows * cols;
        while (left < right && notFound)
        {
            countComparisons++;
            int X = ((left + right) / 2) / rows, Y = ((left + right) / 2) % cols;
            if (array[X][Y] > value)
            {
                right = X * cols + Y;
            }
            else if (array[X][Y] < value)
            {
                left = X * cols + Y + 1;
            }
            else
            {
                notFound = false;
                storage[iStorage] = X, storage[iStorage + 1] = Y;
            }
        }
        iStorage += 2;
    }
    storage[storageSize - 1] = countComparisons;
}

void getHelp()
{
    std::cout << "Using:\n\ttask2.app [path/to/filename] [number] - read array from filename and search number\n\ttask2.app [path/to/filename] --file [path/to/filename2] - read array from filename and search array numbers in filename 2\n\n\tExample task2.app files/t2ex.txt 3\n\n";
}