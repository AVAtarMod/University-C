#include <iostream>
#include <fstream>

#include "list.hpp"

void DEL(intList2D_element *begin);
void DEL(intList1D_element *begin);

void PRINT_begin(const intList1D_element *begin, bool start);
void PRINT_begin(const intList2D_element *begin, bool start);
void PRINT_end(const intList2D_element *end, bool start);

bool INS_UpperSortedRecursion(intList1D_element *begin, int number);
bool INS_UpperSortedCycle(intList1D_element *begin, int number);

void APPEND_Copy(intList1D_element *end, intList1D_element *appendList);
void PUSH_Back(intList1D_element *begin, int number);

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
        PRINT_begin(*list, true);
}

void printFromBegin(const intList1D list)
{
    if (list != nullptr)
        PRINT_begin(*list, true);
}

void printFromEnd(const intList2D list)
{
    if (list != nullptr)
        PRINT_end(*list, true);
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
                return INS_UpperSortedRecursion(*list, number);
            else if (mode == USE_CYCLE)
                return INS_UpperSortedCycle(*list, number);
        }
    }
    return false;
}

intList1D mergeUpperSorted(intList1D sortedListA, intList1D sortedListB)
{
    intList1D merged = new intList1D_element *;
    *merged = new intList1D_element;

    intList1D_element *listptrM = *merged;
    intList1D_element *listptrA = *sortedListA;
    intList1D_element *listptrB = *sortedListB;
    while (listptrA != nullptr && listptrB != nullptr)
    {
        if (listptrA->data < listptrB->data)
        {
            listptrM->next = new intList1D_element;
            listptrM = listptrM->next;

            listptrM->data = listptrA->data;
            listptrA = listptrA->next;
        }
        else
        {
            listptrM->next = new intList1D_element;
            listptrM = listptrM->next;

            listptrM->data = listptrB->data;
            listptrB = listptrB->next;
        }
    }
    intList1D_element *empty = *merged, *begin = (*merged)->next;
    delete empty;
    *merged = begin;

    if (listptrA != nullptr)
        APPEND_Copy(listptrM, listptrA);
    else if (listptrB != nullptr)
        APPEND_Copy(listptrM, listptrB);

    return merged;
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

bool pushBack(intList1D list, int number)
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
            PUSH_Back(*list, number);
        }
    }
    return false;
}

void deleteList(intList2D list)
{
    if (*list != nullptr)
        DEL(*list);
    delete list;
}

void deleteList(intList1D list)
{
    if (*list != nullptr)
        DEL(*list);
    delete list;
}

// ########################################################
// ########################################################
// ########## Private functions ###########################
// ########################################################
// ########################################################

void APPEND_Copy(intList1D_element *end, intList1D_element *appendList)
{
    while (appendList != nullptr)
    {
        end->next = new intList1D_element(appendList->data);
        end = end->next;
        appendList = appendList->next;
    }
}

void PRINT_begin(const intList1D_element *begin, bool start)
{
    if (begin != nullptr)
    {
        if (start)
            std::cout << begin->data;
        else
            std::cout << " " << begin->data;
        PRINT_begin(begin->next, false);
    }
}

void PRINT_begin(const intList2D_element *begin, bool start)
{
    if (begin != nullptr)
    {
        if (start)
            std::cout << begin->data;
        else
            std::cout << " " << begin->data;
        PRINT_begin(begin->next, false);
    }
}

void PRINT_end(const intList2D_element *end, bool start)
{
    if (end != nullptr)
    {
        if (start)
            std::cout << end->data;
        else
            std::cout << " " << end->data;
        PRINT_end(end->previous, false);
    }
}

void DEL(intList1D_element *begin)
{
    intList1D_element *prev = begin, *temp = begin->next;
    while (temp != nullptr)
    {
        delete prev;
        prev = temp;
        temp = temp->next;
    }
    delete prev;
    begin = nullptr;
}

void DEL(intList2D_element *begin)
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

bool INS_Before(intList1D_element *current, int number)
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

void PUSH_Back(intList1D_element *begin, int number)
{
    while (begin->next != nullptr)
    {
        begin = begin->next;
    }
    begin->next = new intList1D_element(number);
}

bool INS_UpperSortedCycle(intList1D_element *current, int number)
{
    while (current->next != nullptr && current->data <= number)
        current = current->next;

    if (current->data > number)
        return INS_Before(current, number);

    else if (current->next == nullptr)
    {
        PUSH_Back(current, number);
        return true;
    }

    return false;
}

bool INS_UpperSortedRecursion(intList1D_element *current, int number)
{
    if (current->data > number)
        return INS_Before(current, number);

    else if (current->next == nullptr)
    {
        PUSH_Back(current, number);
        return true;
    }

    else
        return INS_UpperSortedRecursion(current->next, number);
}