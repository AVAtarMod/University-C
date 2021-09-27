#include <iostream>
#include <fstream>
#include <sstream>

#include "list.hpp"

void DEL(intList2D_element *begin);
void DEL(intList1D_element *begin);

void PRINT_begin(const intList1D_element *begin, bool start);
void PRINT_begin(const intList2D_element *begin, bool start);
void PRINT_end(const intList2D_element *end, bool start);

bool INS_UpperSortedRecursion(intList1D_element *begin, int number);
bool INS_UpperSortedCycle(intList1D_element *begin, int number);

void APPEND_BACK_Copy(intList1D_element *end, intList1D_element *appendList);
void APPEND_BACK_Link(intList1D_element *end, intList1D_element *appendList);
void APPEND_FRONT_Link(intList1D list, intList1D appendList);

void PUSH_Back(intList1D_element *begin, int number);
void PUSH_Front(intList1D_element *begin, int number);

intList1D CONV_sstreamToList1D(std::stringstream &sstream);

bool init(intList1D &list, int number)
{
    if (list == nullptr)
    {
        list = new intList1D_element *;
        if (*list == nullptr)
        {
            *list = new intList1D_element(number);
            return true;
        }
    }
    return false;
}

bool is_inited(const intList1D list)
{
    if (list == nullptr && *list == nullptr)
        return false;
    else
        return true;
}

void appendFront(intList1D list, intList1D appendList)
{
    APPEND_FRONT_Link(list, appendList);
}

int sumChain(const intList2D list)
{
    intList2D_element *begin = *list;
    int sum = 0;
    while (begin != nullptr)
    {
        sum += begin->data;
        begin = begin->next;
    }
    return sum;
}

int greaterThenIndex(const intList2D list, int index)
{
    intList2D_element *begin = *list;
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

int maxElementData(const intList2D list)
{
    intList2D_element *begin = *list;
    int max = 0;
    while (begin != nullptr)
    {
        if (max < begin->data)
            max = begin->data;
        begin = begin->next;
    }
    return max;
}

void printBegin(const intList2D list)
{
    if (list != nullptr)
        PRINT_begin(*list, true);
}

void printBegin(const intList1D list)
{
    if (list != nullptr)
        PRINT_begin(*list, true);
}

void printEnd(const intList2D list)
{
    if (list != nullptr)
        PRINT_end(*list, true);
}

bool insertUpperSorted(intList1D &list, int number, FLAGS mode)
{
    if (list == nullptr || *list == nullptr)
    {
        init(list, number);
        return true;
    }

    if (mode == USE_RECURSION)
        return INS_UpperSortedRecursion(*list, number);
    else if (mode == USE_CYCLE)
        return INS_UpperSortedCycle(*list, number);

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
        APPEND_BACK_Copy(listptrM, listptrA);
    else if (listptrB != nullptr)
        APPEND_BACK_Copy(listptrM, listptrB);

    return merged;
}

intList1D fileToList(const std::string filename)
{
    std::ifstream in(filename);
    intList1D list = nullptr;
    while (!in.eof())
    {
        if (in.fail())
            in.clear();
        int t;
        in >> t;
        pushBack(list, t);
    }
    in.close();
    return list;
}

std::list<intList1D> fileToLists(const std::string filename, const char delimiter)
{
    std::ifstream in(filename);
    int countList = 0;
    while (!in.eof())
    {
        char t;
        in.get(t);
        if (t == delimiter)
            ++countList;
    }
    in.clear();
    in.seekg(0);

    std::list<intList1D> arrayLists;
    std::stringstream temp;
    char buffer[LIST_LIB::BUFFER_SIZE];
    for (; countList > 0; --countList)
    {
        in.getline(buffer, LIST_LIB::BUFFER_SIZE - 1, delimiter);

        int countReplaces = 0;
        int *indexArray = indexSymbols(buffer, '\n', countReplaces);
        replace(buffer, indexArray, countReplaces, ' ');

        temp.str(buffer);
        arrayLists.push_back(CONV_sstreamToList1D(temp));

        if (indexArray != nullptr)
            delete[] indexArray;
    }
    in.close();
    return arrayLists;
}

intList1D readArrayKeyboard(MODE_STOP mode)
{
    intList1D storage = nullptr;
    while (true)
    {
        int t;
        std::cin >> t;
        if ((t == 0 && mode == ZERO) || std::cin.eof())
            break;
        pushBack(storage, t);
    }
    return storage;
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

// TODO support to > 0
/**
 * @brief Cutting list
 * 
 * @param list list, will be cut in range [start;index]
 * @param from start (index)
 * @param to end (index)
 * @return intList1D sublist
 */
intList1D cut(intList1D &list, int from, int to)
{
    try
    {
        if (from > to)
            throw "Incorrect couple 'from - to' for cutting list";
    }
    catch (const char *message)
    {
        std::cerr << message << '\n';
        return nullptr;
    }

    intList1D sublist = new intList1D_element *;
    *sublist = new intList1D_element;
    intList1D_element *list_ptr = *list;

    for (int i = 0; i < from - 1; ++i)
    {
        if (list_ptr->next == nullptr)
            break;
        list_ptr = list_ptr->next;
    }
    intList1D_element *begin_slice = list_ptr;

    APPEND_BACK_Link(*sublist, begin_slice->next);
    begin_slice->next = nullptr;

    if (to == 0)
        to = INT16_MIN + from;
    for (int i = 0; i < from - to + 1; ++i)
    {
        if (list_ptr->next == nullptr)
            break;
        list_ptr = list_ptr->next;
    }

    intList1D_element *end_slice = list_ptr->next;
    begin_slice->next = end_slice;
    list_ptr->next = nullptr;

    intList1D_element *empty = *sublist, *begin = (*sublist)->next;
    delete empty;
    *sublist = begin;

    return sublist;
}

int findFirstOf(const intList1D list, int number)
{
    intList1D_element *list_ptr = *list;
    int index = 0;
    while (list_ptr != nullptr && list_ptr->data != number)
    {
        list_ptr = list_ptr->next;
        ++index;
    }
    if (list_ptr != nullptr && list_ptr->data == number)
        return index;
    else
        return -1;
}

void pushBack(intList1D &list, int number)
{
    if (!init(list, number))
        PUSH_Back(*list, number);
}

void pushFront(intList1D &list, int number)
{
    if (!init(list, number))
        PUSH_Front(*list, number);
}

void deleteList(intList2D list)
{
    if (list != nullptr)
    {
        if (*list != nullptr)
            DEL(*list);
        delete list;
    }
}

void deleteList(intList1D list)
{
    if (list != nullptr)
    {
        if (*list != nullptr)
            DEL(*list);
        delete list;
    }
}

intList1D reverse(const intList1D source)
{
    if (is_inited(source))
    {
        intList1D rotated = nullptr;
        intList1D_element *begin = *source;
        while (begin != nullptr)
        {
            pushFront(rotated, begin->data);
            begin = begin->next;
        }
        return rotated;
    }
    return nullptr;
}

intList1D filter(const intList1D source, bool comparator(int))
{
    if (is_inited(source))
    {
        intList1D filtered = nullptr;
        intList1D_element *current = *source;
        int current_data;

        while (current != nullptr)
        {
            current_data = current->data;
            if (comparator(current_data))
                pushBack(filtered, current_data);
            current = current->next;
        }
        return filtered;
    }
    return nullptr;
}

intList1D mergeByAction(const intList1D listA, const intList1D listB, int action(int fromA, int fromB))
{
    intList1D merged = new intList1D_element *;
    *merged = new intList1D_element;

    intList1D_element *listptrM = *merged;
    intList1D_element *listptrA = *listA;
    intList1D_element *listptrB = *listB;
    while (listptrA != nullptr || listptrB != nullptr)
    {
        listptrM->next = new intList1D_element;
        listptrM = listptrM->next;
        if (listptrA == nullptr)
        {
            listptrM->data = action(0, listptrB->data);
            listptrB = listptrB->next;
        }
        else if (listptrB == nullptr)
        {
            listptrM->data = action(listptrA->data, 0);
            listptrA = listptrA->next;
        }
        else
        {
            listptrM->data = action(listptrA->data, listptrB->data);
            listptrA = listptrA->next;
            listptrB = listptrB->next;
        }
    }
    intList1D_element *empty = *merged, *begin = (*merged)->next;
    delete empty;
    *merged = begin;

    return merged;
}

namespace comparator
{
    bool positive(int number) { return number > 0; }
    bool negative(int number) { return number < 0; }

} // namespace comparator

namespace action
{
    int sum(int a, int b) { return a + b; }
} // namespace action

// ########################################################
// ########################################################
// ########## Private functions ###########################
// ########################################################
// ########################################################

intList1D CONV_sstreamToList1D(std::stringstream &sstream)
{
    intList1D list = nullptr;
    while (!sstream.eof())
    {
        int sstream_data;
        sstream >> sstream_data;
        pushBack(list, sstream_data);
    }
    sstream.clear();
    return list;
}

void APPEND_BACK_Copy(intList1D_element *end, intList1D_element *appendList)
{
    while (appendList != nullptr)
    {
        end->next = new intList1D_element(appendList->data);
        end = end->next;
        appendList = appendList->next;
    }
}

void APPEND_BACK_Link(intList1D_element *end, intList1D_element *appendList)
{
    end->next = appendList;
}

void APPEND_FRONT_Link(intList1D list, intList1D appendList)
{
    intList1D_element *list_ptr = *list;
    intList1D_element *appendList_ptr = *appendList;
    while (appendList_ptr->next != nullptr)
        appendList_ptr = appendList_ptr->next;
    appendList_ptr->next = list_ptr;
    list_ptr = appendList_ptr;
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

void PUSH_Front(intList1D_element *begin, int number)
{
    INS_Before(begin, number);
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