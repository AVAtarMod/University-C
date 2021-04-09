#include <iostream>
#include <map>

#include "Data.hpp"
#include "arrays1d.hpp"
#include "algorithms.hpp"

#define EXPECTED_SORT arrays1d::NOT_DECREASING

#define pair std::pair<uint16_t, uint16_t>

namespace userInput
{
    uint32_t getDataUser(uint32_t &n, uint32_t &m);
}

void task1(uint32_t n = 0, uint32_t m = 0);
void task2(uint32_t n = 0, uint32_t m = 0);
void task3(uint32_t n = 0, uint32_t m = 0);

template <class T>
void printTaskComplete(T task)
{
    std::cout << "\n\nTask #" << task << " complete.\n";
}

int main(int argc, char const *argv[])
{
    uint32_t numberTask, n, m;

    switch (argc)
    {
    case 1:
        numberTask = userInput::getDataUser(n, m);
        break;
    case 2:
        numberTask = static_cast<uint32_t>(atoi(argv[1]));
        break;
    case 4:
        numberTask = static_cast<uint32_t>(atoi(argv[1]));
        n = static_cast<uint32_t>(atoi(argv[2]));
        m = static_cast<uint32_t>(atoi(argv[3]));
        break;

    default:
        break;
    }

    switch (numberTask)
    {
    case 1:
        task1(n, m);
        printTaskComplete(1);
        break;
    case 2:
        task2(n, m);
        printTaskComplete(2);
        break;
    case 3:
        task3(n, m);
        printTaskComplete(3);
        break;

    default:
        break;
    }
    return 0;
}

void task1(uint32_t n, uint32_t m)
{
    uint16_t *array = new uint16_t[n];
    arrays1d::generateRandom(array, n, 0, m);
    arrays1d::print(array, n);
    std::map<uint16_t, uint16_t> indexMap;
    for (uint16_t i = 0; i < n; i++)
    {
        if (indexMap.find(array[i]) == indexMap.end())
            indexMap.insert({array[i], 1});
        else
            indexMap.at(array[i])++;
    }

    uint16_t index = 0;
    for (auto i : indexMap)
        for (uint16_t iAr = 0; iAr < i.second; ++iAr, ++index)
            array[index] = i.first;

    arrays1d::print(array, n);
    delete[] array;
}
void task2(uint32_t n, uint32_t m)
{
    uint16_t *array = new uint16_t[n];
    arrays1d::generateRandom(array, n, -m, m);
    arrays1d::print(array, n);

    uint16_t *arraySorted = new uint16_t[n];
    uint16_t iS = 0;
    for (uint16_t i = 0; i < n; i++)
        if (array[i] % 2 == 0)
        {
            arraySorted[iS] = array[i];
            iS++;
        }
    for (uint16_t i = 0; i < n; i++)
        if (array[i] % 2 == 1)
        {
            arraySorted[iS] = array[i];
            iS++;
        }

    arrays1d::print(array, n);
    delete[] array, delete[] arraySorted;
}
void task3(uint32_t n, uint32_t m)
{
    int *ar = new int[n];
    arrays1d::generate(ar, n, arrays1d::RANDOMLY, 0, m);
    std::cout << "\n";
    arrays1d::print(ar, n);
    std::cout << "Ecxchange " << simpleExchange(ar, n);
    arrays1d::print(ar, n);
    arrays1d::generate(ar, n, arrays1d::RANDOMLY, 0, m);
    std::cout << "\n";
    arrays1d::print(ar, n, "new");
    std::cout << "Select " << simpleSelection(ar, n);
    arrays1d::print(ar, n);

    //----
    arrays1d::generate(ar, n, arrays1d::RANDOMLY, 0, m);
    std::cout << "\n";
    arrays1d::print(ar, n,"new");
    std::cout << "Shaker " << shakerSort(ar, n);
    arrays1d::print(ar, n);
    arrays1d::generate(ar, n, arrays1d::RANDOMLY, 0, m);
    std::cout << "\n";
    arrays1d::print(ar, n, "new");
    std::cout << "Insertion " << insertion(ar, n);
    arrays1d::print(ar, n);
    delete[] ar;
}

namespace userInput
{
    uint32_t getDataUser(uint32_t &n, uint32_t &m)
    {
        while (true)
        {
            std::cout << "Enter task number[1-3]: ";
            uint32_t number;
            std::cin >> number;
            std::cout << "Enter n,m through space (ex 1 2): ";
            std::cin >> n >> m;
            if (!std::cin.good())
                std::cout << "Please try again...";
            else
                return number;
            std::cin.ignore(INT16_MAX, '\n');
            std::cin.clear();
        }
        return 0;
    }
} // namespace userInput
