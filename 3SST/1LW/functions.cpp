#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

#include "functions.hpp"

int getRandomNumber(int from, int to)
{
    try
    {
        if (from > to)
            throw "Incorrect couple 'from - to' for generating random numbers";
    }
    catch (const char *message)
    {
        std::cerr << message << '\n';
        exit(1);
    }

    unsigned int now = static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count() % 10000);
    std::mt19937 engine(now);
    std::uniform_int_distribution<int> random(from, to);

    return random(engine);
}

int sumChain(intList2D_element *begin)
{
    int sum = 0;
    while (begin != nullptr)
    {
        sum += begin->data;
        begin = begin->next;
    }
    return sum;
}

int greaterThenIndex(intList2D_element *begin, int index)
{
    int cur_index = 0;
    int index_data = 0;
    int greater = 0;

    intList2D_element *tmp = begin;
    for (int i = 0; i < index; ++i, tmp = tmp->next)
    {
    }

    index_data = tmp->data;
    tmp = begin;

    while (tmp != nullptr)
    {
        if (cur_index != index && tmp->data > index_data)
        {
            ++greater;
        }
        tmp = tmp->next;
        ++cur_index;
    }
    return greater;
}

int maxElementData(intList2D_element *begin)
{
    int max = 0;
    while (begin != nullptr)
    {
        if (max < begin->data)
            max = begin->data;
        begin = begin->next;
    }
    return max;
}

void printFromBegin(intList2D_element *begin, bool start)
{
    if (begin != nullptr)
    {
        if (start)
            std::cout << begin->data;
        else
            std::cout << " " << begin->data;
        printFromBegin(begin->next, false);
    }
}

void printFromEnd(intList2D_element *end, bool start)
{
    if (end != nullptr)
    {
        if (start)
            std::cout << end->data;
        else
            std::cout << " " << end->data;
        printFromEnd(end->previous, false);
    }
}

void del(intList2D_element *begin)
{
    intList2D_element *prev = begin, *temp = begin->next;
    while (temp != nullptr)
    {
        delete prev;
        prev = temp;
        temp = temp->next;
    }
    delete prev;
    begin = nullptr;
}

std::list<int> readArrayFile(std::string filename)
{
    std::ifstream in(filename);
    std::list<int> list;
    while (!in.eof())
    {
        if (in.fail())
            in.clear();
        int t;
        in >> t;
        list.push_back(t);
    }
    in.close();
    return list;
}

std::list<int> readArrayKeyboard(MODE_STOP mode)
{
    std::list<int> list;
    while (!std::cin.eof())
    {
        int t;
        std::cin >> t;
        if (t == 0 && mode == ZERO)
            break;
        list.push_back(t);
    }
    return list;
}