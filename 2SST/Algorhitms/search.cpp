#include <iostream>
#include <vector>
#include <algorithm>

#include "../../1SST/LABW13/arrays2d.cpp"
#include "../../1SST/LABW13/useful.h"
#include "cpp-text-table/TextTable.h"

const int SIZE = 100; //000000;
enum ValuePlace
{
    AT_BEGIN,
    AT_MIDDLE,
    AT_END,
    NOT_EXIST
};

std::vector<uint32_t> getArray(int value, ValuePlace placeOfValue, bool needSort = false);

TextTable getTable(uint64_t linear[4], uint64_t linearBarrier[4], uint64_t binary[4], uint64_t binaryRecursive[4]);

int linear(std::vector<uint32_t> array, int value);
int linearWithBarrier(std::vector<uint32_t> array, int value);
int binary(std::vector<uint32_t> array, int value);
int binaryRecursive(std::vector<uint32_t> array, int value, int l = 0, int r = SIZE - 1, int c = 0);

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "ru_RU.UTF8");
    std::cout << "Enter value for search (for binary search not work): " << fgGreen;
    int value;
    std::cin >> value;
    std::cout << reset << "\nStatus: " << fgGreen;

    uint64_t linearResultA[4];
    uint64_t linearBarrierA[4];
    uint64_t binaryA[4];
    uint64_t binaryRecursiveA[4];

    //------------------
    std::vector<uint32_t> array = getArray(value, AT_BEGIN);
    linearResultA[0] = linear(array, value);
    linearBarrierA[0] = linearWithBarrier(array, value);

    array = getArray(value, AT_BEGIN, true);
    binaryA[0] = binary(array, 0);
    binaryRecursiveA[0] = binaryRecursive(array, 0);
    std::cout << "25%";
    std::cout.flush();

    //------------------
    array = getArray(value, AT_MIDDLE);
    linearResultA[1] = linear(array, value);
    linearBarrierA[1] = linearWithBarrier(array, value);

    array = getArray(value, AT_MIDDLE, true);
    binaryA[1] = binary(array, SIZE / 2);
    binaryRecursiveA[1] = binaryRecursive(array, SIZE / 2);
    std::cout << "\b\b\b50%";
    std::cout.flush();

    //------------------
    array = getArray(value, AT_END);
    linearResultA[2] = linear(array, value);
    linearBarrierA[2] = linearWithBarrier(array, value);

    array = getArray(value, AT_END, true);
    binaryA[2] = binary(array, SIZE - 1);
    binaryRecursiveA[2] = binaryRecursive(array, SIZE - 1);
    std::cout << "\b\b\b75%";
    std::cout.flush();

    //------------------
    array = getArray(value, NOT_EXIST);
    linearResultA[3] = linear(array, value);
    linearBarrierA[3] = linearWithBarrier(array, value);
    array = getArray(value, NOT_EXIST, true);
    binaryA[3] = binary(array, -1);
    binaryRecursiveA[3] = binaryRecursive(array, -1);
    std::cout << "\b\b\b100%" << reset << "\n";

    std::cout << getTable(linearResultA, linearBarrierA, binaryA, binaryRecursiveA);
}

int linear(std::vector<uint32_t> array, int value)
{
    int countComparisons = 0;
    for (int i = 0; i < SIZE; i++)
    {
        countComparisons += 2;
        if (array.at(i) == value)
            return countComparisons;
    }
    return countComparisons;
}

int linearWithBarrier(std::vector<uint32_t> array, int value)
{
    uint32_t lastElement = array.at(SIZE - 1);
    array.at(SIZE - 1) = value;
    uint32_t i = 0;
    uint32_t countComparisons = 1;
    while (array.at(i) != value)
    {
        countComparisons++;
        i++;
    }

    return countComparisons;
}
int binary(std::vector<uint32_t> array, int value)
{
    uint32_t countComparisons = 0;
    int left = 0, right = SIZE;
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

int binaryRecursive(std::vector<uint32_t> array, int value, int l, int r, int c)
{
    bool notFound = true;
    if (l <= r && notFound)
    {
        int middle = (l + r) / 2;
        if (array.at(middle) > value)
        {
            c++;
            return binaryRecursive(array, value, 0, middle, c);
        }
        else if (array.at(middle) < value)
        {
            c++;
            return binaryRecursive(array, value, middle + 1, r, c);
        }
        else if (array.at(middle) == value)
        {
            notFound = false;
            c++;
        }
    }
    return c;
}

std::vector<uint32_t> getArray(int value, ValuePlace placeOfValue, bool needSort)
{

    std::vector<uint32_t> array;
    array.resize(SIZE);
    if (needSort)
        for (int i = 0; i < SIZE - 1; i++)
            array.at(i) = i;
    else
        switch (placeOfValue)
        {
        case AT_BEGIN:
            array[0] = value;
            for (size_t i = 1; i < SIZE; i++)
            {
                do
                {
                    array.at(i) = getRandomNumber(-100, 100);
                } while (array[i] == value);
            }
            break;
        case AT_MIDDLE:
            array[SIZE / 2] = value;
            for (size_t i = 0; i < SIZE; i++)
            {
                if (i != SIZE / 2)
                    do
                    {
                        array.at(i) = getRandomNumber(-100, 100);
                    } while (array[i] == value);
            }
            break;
        case AT_END:
            array[SIZE] = value;
            for (size_t i = 0; i < SIZE - 1; i++)
            {
                do
                {
                    array.at(i) = getRandomNumber(-100, 100);
                } while (array[i] == value);
            }
            break;
        case NOT_EXIST:
            for (size_t i = 0; i < SIZE; i++)
            {
                do
                {
                    array.at(i) = getRandomNumber(-100, 100);
                } while (array[i] == value);
            }
            break;
        default:
            break;
        }
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