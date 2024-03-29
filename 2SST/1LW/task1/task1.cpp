#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#include "/home/grigory/Programming/C++/Laboratory/1SST/LABW13/arrays2d.cpp"
#include "/home/grigory/Programming/C++/Laboratory/1SST/LABW13/useful.h"
#include "/home/grigory/Programming/C++/Laboratory/2SST/LABW1/extension/cpp-text-table/TextTable.h"

const int SIZE = 100'000'000; //
enum ValuePlace
{
    AT_BEGIN,
    AT_MIDDLE,
    AT_END,
    NOT_EXIST
};

uint32_t *getArray();

TextTable getTable(uint64_t linear[4], uint64_t linearBarrier[4], uint64_t binary[4], uint64_t binaryRecursive[4]);

int linear(uint32_t *array, int value);
int linearWithBarrier(uint32_t *array, int value);
int binary(uint32_t *array, int value);
int binaryRecursive(uint32_t *array, int value, int l = 0, int r = SIZE - 1, int c = 0);

int main(int argc, char const *argv[])
{
    int value = 0;

    uint64_t linearResultA[4];
    uint64_t linearBarrierA[4];
    uint64_t binaryA[4];
    uint64_t binaryRecursiveA[4];

    //------------------
    uint32_t *array = getArray();
    std::cout << "\b\b5%";
    std::cout.flush();
    linearResultA[0] = linear(array, 0);
    std::cout << "\b\b10%";
    std::cout.flush();
    linearBarrierA[0] = linearWithBarrier(array, 0);

    std::cout << "\b\b\b25%";
    std::cout.flush();
    delete[] array;
    array = getArray();
    binaryA[0] = binary(array, 0);
    binaryRecursiveA[0] = binaryRecursive(array, 0);

    //------------------
    delete[] array;
    array = getArray();
    linearResultA[1] = linear(array, SIZE / 2 - 1);
    linearBarrierA[1] = linearWithBarrier(array, SIZE / 2 - 1);

    delete[] array;
    array = getArray();
    binaryA[1] = binary(array, SIZE / 2 - 1);
    binaryRecursiveA[1] = binaryRecursive(array, SIZE / 2 - 1);
    std::cout << "\b\b\b50%";
    std::cout.flush();

    //------------------
    delete[] array;
    array = getArray();
    linearResultA[2] = linear(array, SIZE - 1);
    linearBarrierA[2] = linearWithBarrier(array, SIZE - 1);

    delete[] array;
    array = getArray();
    binaryA[2] = binary(array, SIZE - 1);
    binaryRecursiveA[2] = binaryRecursive(array, SIZE - 1);
    std::cout << "\b\b\b75%";
    std::cout.flush();

    //------------------
    delete[] array;
    array = getArray();
    linearResultA[3] = linear(array, -1);
    linearBarrierA[3] = linearWithBarrier(array, -1);
    array = getArray();
    binaryA[3] = binary(array, -1);
    binaryRecursiveA[3] = binaryRecursive(array, -1);
    std::cout << "\b\b\b100%" << reset << "\n";

    delete[] array;

    TextTable result = getTable(linearResultA, linearBarrierA, binaryA, binaryRecursiveA);
    std::cout << result;

    std::ofstream out("/home/grigory/Programming/C++/Laboratory/2SST/LABW1/files/task1_out.txt", out.trunc);
    if (out.good())
    {
        out << result;
    }
    out.close();
}

int linear(uint32_t *array, int value)
{
    int countComparisons = 0;
    for (int i = 0; i < SIZE; i++)
    {
        countComparisons += 2;
        if (array[i] == value)
            return countComparisons;
    }
    return countComparisons;
}

int linearWithBarrier(uint32_t *array, int value)
{
    uint32_t lastElement = array[SIZE - 1];
    array[SIZE - 1] = value;
    uint32_t i = 0;
    uint32_t countComparisons = 1;
    while (array[i] != value)
    {
        countComparisons++;
        i++;
    }
    if (lastElement == value);
    countComparisons++;

    return countComparisons;
}
int binary(uint32_t *array, int value)
{
    uint32_t countComparisons = 0;
    int left = 0, right = SIZE - 1;
    bool notFound = true;
    while (left <= right && notFound)
    {
        int middle = (left + right) / 2;
        if (array[middle] > value)
            right = middle;
        else if (array[middle] < value)
            left = middle + 1;
        else
            notFound = false;
        countComparisons++;
    }

    return countComparisons;
}

int binaryRecursive(uint32_t *array, int value, int l, int r, int c)
{
    if (l < r)
    {
        int middle = (l + r) / 2;
        if (array[middle] > value)
        {
            c++;
            return binaryRecursive(array, value, 0, middle, c);
        }
        else if (array[middle] < value)
        {
            c++;
            return binaryRecursive(array, value, middle + 1, r, c);
        }
        c++;
    }
    return c;
}

uint32_t *getArray()
{
    uint32_t *array = new uint32_t[SIZE];
    for (int i = 0; i < SIZE - 1; i++)
        array[i] = i;

    return array;
}

TextTable getTable(uint64_t linear[4], uint64_t linearBarrier[4], uint64_t binary[4], uint64_t binaryRecursive[4])
{
    TextTable table;
    table.add("");
    table.add("FIRST");
    table.add("IN THE MIDDLE");
    table.add("AT END");
    table.add("NOT EXIST");
    table.endOfRow();

    table.add("Linear search");
    table.add(std::to_string(linear[0]));
    table.add(std::to_string(linear[1]));
    table.add(std::to_string(linear[2]));
    table.add(std::to_string(linear[3]));
    table.endOfRow();

    table.add("linear with barrier");
    table.add(std::to_string(linearBarrier[0]));
    table.add(std::to_string(linearBarrier[1]));
    table.add(std::to_string(linearBarrier[2]));
    table.add(std::to_string(linearBarrier[3]));
    table.endOfRow();

    table.add("binary");
    table.add(std::to_string(binary[0]));
    table.add(std::to_string(binary[1]));
    table.add(std::to_string(binary[2]));
    table.add(std::to_string(binary[3]));
    table.endOfRow();

    table.add("binary recursive");
    table.add(std::to_string(binaryRecursive[0]));
    table.add(std::to_string(binaryRecursive[1]));
    table.add(std::to_string(binaryRecursive[2]));
    table.add(std::to_string(binaryRecursive[3]));
    table.endOfRow();
    table.setAlignment(2, TextTable::Alignment::LEFT);

    return table;
}