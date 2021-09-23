#include <iostream>
#include <fstream>

#include "list.hpp"

void prntFB_1D(const intList1D_element *begin, bool start);
void prntFB_2D(const intList2D_element *begin, bool start);
void prntFE_2D(const intList2D_element *end, bool start);
bool insertUpperSortedRecursion(intList1D_element *begin, int number);
bool insertUpperSortedCycle(intList1D_element *begin, int number);

int sumChain(const intList2D_element *begin)
{
    int sum = 0;
    while (begin != nullptr)
    {
        sum += begin->data;
        begin = begin->next;
    }
    return sum;
}

int greaterThenIndex(const intList2D_element *begin, int index)
{
    int cur_index = 0;
    int index_data = 0;
    int greater = 0;

    const intList2D_element *tmp = begin;
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

int maxElementData(const intList2D_element *begin)
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

void printFromBegin(const intList2D list)
{
    if (list != nullptr)
        prntFB_2D(*list, true);
}

void printFromBegin(const intList1D list)
{
    if (list != nullptr)
        prntFB_1D(*list, true);
}

void printFromEnd(const intList2D list)
{
    if (list != nullptr)
        prntFE_2D(*list, true);
}

void prntFB_1D(const intList1D_element *begin, bool start)
{
    if (begin != nullptr)
    {
        if (start)
            std::cout << begin->data;
        else
            std::cout << " " << begin->data;
        prntFB_1D(begin->next, false);
    }
}

void prntFB_2D(const intList2D_element *begin, bool start)
{
    if (begin != nullptr)
    {
        if (start)
            std::cout << begin->data;
        else
            std::cout << " " << begin->data;
        prntFB_2D(begin->next, false);
    }
}

void prntFE_2D(const intList2D_element *end, bool start)
{
    if (end != nullptr)
    {
        if (start)
            std::cout << end->data;
        else
            std::cout << " " << end->data;
        prntFE_2D(end->previous, false);
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

bool insert(intList2D_element *begin, int index, int number)
{
    while (index != 1 && begin != nullptr)
    {
        begin = begin->next;
        --index;
    }
    if (index == 1)
    {
        intList2D_element *temp = new intList2D_element(begin, number, begin->next);
        begin->next = temp;

        if (begin->next != nullptr)
            begin->next->previous = temp;
        return true;
    }
    else
        return false;
}

bool insert(intList1D_element *begin, int index, int number)
{
    while (index != 1 && begin != nullptr)
    {
        begin = begin->next;
        --index;
    }
    if (index == 1)
    {
        intList1D_element *temp = new intList1D_element(number, begin->next);
        begin->next = temp;

        return true;
    }
    else
        return false;
}

bool insertBefore(intList1D_element *current, int number)
{
    if (current != nullptr)
    {
        intList1D_element *temp = new intList1D_element(current->data, current->next);
        current->data = number;
        current->next = temp;

        return true;
    }
    else
        return false;
}

bool pushBack(intList1D_element *begin, int number)
{
    while (begin->next != nullptr)
    {
        begin = begin->next;
    }
    intList1D_element *tmp = new intList1D_element(number);
    begin->next = tmp;
    if (begin->next == tmp)
        return true;
    else
        return false;
}

bool insertUpperSorted(intList1D list, int number, FLAGS mode)
{
    if (list != nullptr)
    {
        if (*list == nullptr)
        {
            *list = new intList1D_element(number);
            return true;
        }
        else
        {
            if (mode == USE_RECURSION)
                return insertUpperSortedRecursion(*list, number);
            else if (mode == USE_CYCLE)
                return insertUpperSortedCycle(*list, number);
        }
    }
    return false;
}

bool insertUpperSortedCycle(intList1D_element *current, int number)
{
    while (current->next != nullptr && current->data <= number)
        current = current->next;

    if (current->data > number)
        return insertBefore(current, number);

    else if (current->next == nullptr)
        return pushBack(current, number);

    return false;
}

bool insertUpperSortedRecursion(intList1D_element *current, int number)
{
    if (current->data > number)
        return insertBefore(current, number);

    else if (current->next == nullptr)
        return pushBack(current, number);

    else
        return insertUpperSortedRecursion(current->next, number);
}

intList1D mergeUpperSorted(intList1D sortedListA, intList1D sortedListB)
{
    intList1D_element *listptrA = *sortedListA;
    intList1D_element *listptrB = *sortedListB;
    
}