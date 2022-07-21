#include <array>
#include <fstream>
#include <iostream>
#include <string>

#include "../extension/arrays2d.cpp"
#include "../extension/cpp-text-table/TextTable.h"

const int rows = 5;
const int collumns = 5;
const int sizeResultArrays = 5;

void linear(int** array, int value, int* storage, int placeResult = 2);
void linearWithBorder(int** array, int value, int* storage, int placeResult = 2);
TextTable getResult(int* resultLinear, int* resultBorder);

int main(int argc, char const* argv[])
{
    int** array = array2d::init(rows, collumns);
    int number;

    int* resultLinear = new int[sizeResultArrays] { -1 };
    int* resultBorder = new int[sizeResultArrays] { -1 };

    bool silentMode = (argc > 1 && std::string(argv[1]) == "-s") ? true : false;

    if (silentMode) {
        array2d::fill(array, rows, collumns);
        number = array[0][0];

        linear(array, number, resultLinear);
        linear(array, array[rows / 2][collumns / 2], resultLinear, 3);
        linear(array, -1, resultLinear, 4);

        linearWithBorder(array, number, resultBorder);
        linearWithBorder(array, array[rows / 2][collumns / 2], resultBorder, 3);
        linearWithBorder(array, -1, resultBorder, 4);

        TextTable result = getResult(resultLinear, resultBorder);
        std::ofstream out("../files/task2_out.txt", out.trunc);
        if (out.good()) {
            out << result;
            out.close();
        }
        std::cout << result;
    } else {
        std::string text = std::to_string(rows) + "x" + std::to_string(collumns);
        array2d::fillUser(array, rows, collumns, text.c_str());
        std::cout << "Enter number for search: ";
        std::cin >> number;

        linear(array, number, resultLinear);
        linearWithBorder(array, number, resultBorder);
        if (*resultLinear == -1 && *resultBorder == *resultLinear) {
            std::cout << "\nNumber not found\n";
        } else
            std::cout << "\nIndex number: [" << resultLinear[0] + 1 << "][" << resultLinear[1] + 1 << "]\n";
    }

    array2d::delete_(array, rows);
    delete[] resultLinear;
    delete[] resultBorder;

    return 0;
}

void linear(int** array, int value, int* storage, int placeResult)
{
    int countComparisons = 0;
    for (uint16_t r = 0; r < rows; r++) {
        for (uint16_t c = 0; c < collumns; c++) {
            countComparisons++;
            if (array[r][c] == value) {
                storage[0] = r, storage[1] = c, storage[placeResult] = countComparisons;
                return;
            }
        }
    }
    storage[placeResult] = countComparisons;
    return;
}

void linearWithBorder(int** array, int value, int* storage, int placeResult)
{
    int countComparisons = 1;
    for (uint16_t r = 0; r < rows; r++) {
        int lastElement = array[r][collumns - 1];
        array[r][collumns - 1] = value;
        int i = 0;
        while (array[r][i] != value) {
            i++;
            countComparisons++;
        }
        if (value == lastElement || i < collumns - 1) {
            storage[0] = r, storage[1] = i, storage[placeResult] = countComparisons;
            return;
        }
    }
    storage[placeResult] = countComparisons;
    return;
}

TextTable getResult(int* resultLinear, int* resultBorder)
{
    std::array<std::string, 4> row1 {
        "",
        "AT BEGIN",
        "MIDDLE",
        "NOT EXIST"
    };
    std::array<std::string, 4> row2 {
        "linear",
        std::to_string(resultLinear[2]),
        std::to_string(resultLinear[3]),
        std::to_string(resultLinear[4])
    };
    std::array<std::string, 4> row3 {
        "linearWithBarrier",
        std::to_string(resultBorder[2]),
        std::to_string(resultBorder[3]),
        std::to_string(resultBorder[4])
    };

    TextTable table;
    table.addRow(row1);
    table.addRow(row2);
    table.addRow(row3);
    table.setAlignment(1, TextTable::Alignment::LEFT);

    return table;
}