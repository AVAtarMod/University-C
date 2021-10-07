#include <iostream>
#include <fstream>
#include <sstream>

#include "list.hpp"

void DEL(IntList2D_element *begin);
void DEL(IntList1D_element *begin);

void PRINT_begin(const IntList1D_element *begin, bool start);
void PRINT_begin(const IntList2D_element *begin, bool start);
void PRINT_end(const IntList2D_element *end, bool start);

bool INS_UpperSortedRecursion(IntList1D_element *begin, int number);
bool INS_UpperSortedCycle(IntList1D_element *begin, int number);

void APPEND_BACK_Copy(IntList1D_element *end, IntList1D_element *appendList);
void APPEND_BACK_Link(IntList1D_element *end, IntList1D_element *appendList);
void APPEND_FRONT_Link(IntList1D list, IntList1D appendList);

void PUSH_Back(IntList1D_element *begin, int number);
void PUSH_Back(IntList1D_element *begin, IntList1D_element *element);
bool PUSH_Before(IntList1D_element *current, int number);
void PUSH_Front(IntList1D_element *begin, int number);

IntList1D_element *POP_Back(IntList1D_element *begin);

IntList1D GEN_USERINPUT_newline(const uint &buffer_size, bool &printInfo);

IntList1D CONV_sstreamToList1D(std::stringstream &sstream);

bool init(IntList1D &list, int number)
{
    if (list == nullptr)
    {
        list = new IntList1D_element *;
        *list = new IntList1D_element(number);
        return true;
    }
    return false;
}

bool init(IntList1D &list, IntList1D_element *element)
{
    if (list == nullptr)
    {
        list = new IntList1D_element *;
        *list = element;
        return true;
    }
    return false;
}

bool is_inited(const IntList1D list)
{
    if (list == nullptr || *list == nullptr)
        return false;
    else
        return true;
}

void appendFront(IntList1D list, IntList1D appendList)
{
    APPEND_FRONT_Link(list, appendList);
}

void appendBack(IntList1D &list, IntList1D appendList)
{
    if (is_inited(appendList))
    {
        if (is_inited(list))
        {
            IntList1D_element *list_ptr = *list;
            while (list_ptr->next != nullptr)
                list_ptr = list_ptr->next;
            APPEND_BACK_Link(list_ptr, *appendList);
        }
        else
            init(list, *appendList);
    }
}

int sumChain(const intList2D list)
{
    IntList2D_element *begin = *list;
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
    IntList2D_element *begin = *list;
    int cur_index = 0;
    int index_data = 0;
    int greater = 0;

    const IntList2D_element *tmp = begin;
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
    IntList2D_element *begin = *list;
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

void printBegin(const IntList1D list)
{
    if (list != nullptr)
        PRINT_begin(*list, true);
}

void printEnd(const intList2D list)
{
    if (list != nullptr)
        PRINT_end(*list, true);
}

bool insertUpperSorted(IntList1D &list, int number, FLAGS mode)
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

IntList1D mergeUpperSorted(IntList1D listA, IntList1D listB, bool listsAlreadySorted)
{
    IntList1D merged = new IntList1D_element *;
    *merged = new IntList1D_element;

    IntList1D_element *listptrM = *merged;
    IntList1D_element *listptrA;
    IntList1D_element *listptrB;

    if (is_inited(listA))
        listptrA = *listA;
    else
        listptrA = nullptr;

    if (is_inited(listB))
        listptrA = *listB;
    else
        listptrA = nullptr;

    while (listptrA != nullptr && listptrB != nullptr)
    {
        if (listptrA->data < listptrB->data)
        {
            listptrM->next = new IntList1D_element;
            listptrM = listptrM->next;

            listptrM->data = listptrA->data;
            listptrA = listptrA->next;
        }
        else
        {
            listptrM->next = new IntList1D_element;
            listptrM = listptrM->next;

            listptrM->data = listptrB->data;
            listptrB = listptrB->next;
        }
    }
    IntList1D_element *empty = *merged, *begin = (*merged)->next;
    delete empty;
    *merged = begin;

    if (listptrA != nullptr)
    {
        if (listsAlreadySorted)
            APPEND_BACK_Copy(listptrM, listptrA);
        else
            while (listptrA != nullptr)
            {
                insertUpperSorted(merged, listptrA->data);
                listptrA = listptrA->next;
            }
    }
    else if (listptrB != nullptr)
    {
        if (listsAlreadySorted)
            APPEND_BACK_Copy(listptrM, listptrB);
        else
            while (listptrB != nullptr)
            {
                insertUpperSorted(merged, listptrB->data);
                listptrB = listptrB->next;
            }
    }

    return merged;
}

IntList1D mergeByAction(const IntList1D listA, const IntList1D listB, int merge_actions(int fromA, int fromB))
{
    IntList1D merged = new IntList1D_element *;
    *merged = new IntList1D_element;

    IntList1D_element *listptrM = *merged;
    IntList1D_element *listptrA = *listA;
    IntList1D_element *listptrB = *listB;
    while (listptrA != nullptr || listptrB != nullptr)
    {
        listptrM->next = new IntList1D_element;
        listptrM = listptrM->next;
        if (listptrA == nullptr)
        {
            listptrM->data = merge_actions(0, listptrB->data);
            listptrB = listptrB->next;
        }
        else if (listptrB == nullptr)
        {
            listptrM->data = merge_actions(listptrA->data, 0);
            listptrA = listptrA->next;
        }
        else
        {
            listptrM->data = merge_actions(listptrA->data, listptrB->data);
            listptrA = listptrA->next;
            listptrB = listptrB->next;
        }
    }
    IntList1D_element *empty = *merged, *begin = (*merged)->next;
    delete empty;
    *merged = begin;

    return merged;
}

IntList1D fileToList(const std::string filename)
{
    std::ifstream in(filename);
    IntList1D list = nullptr;
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

std::list<IntList1D> fileToLists(const std::string filename, const char delimiter)
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

    std::list<IntList1D> arrayLists;
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

/**
 * @brief 
 * 
 * @param mode one from MODE_STOP
 * @param buffer_size optional, use if mode is NEWLINE
 * @param printInfo optional, use if mode is NEWLINE
 * @return IntList1D 
 */
IntList1D readArrayKeyboard(MODE_STOP mode, uint buffer_size, bool printInfo)
{
    IntList1D storage = nullptr;
    if (mode == ZERO || mode == IO_EOF)
    {
        while (true)
        {
            int t;
            std::cin >> t;
            if ((t == 0 && mode == ZERO) || std::cin.eof())
                break;
            pushBack(storage, t);
        }
    }
    else if (mode == NEWLINE)
        return GEN_USERINPUT_newline(buffer_size, printInfo);
    return storage;
}

bool insert(IntList2D_element *begin, int index, int number)
{
    while (index != 1 && begin != nullptr)
    {
        begin = begin->next;
        --index;
    }
    if (index == 1)
    {
        IntList2D_element *temp = new IntList2D_element(begin, number, begin->next);
        begin->next = temp;

        if (begin->next != nullptr)
            begin->next->previous = temp;
        return true;
    }
    else
        return false;
}

bool insert(IntList1D_element *begin, int index, int number)
{
    while (index != 1 && begin != nullptr)
    {
        begin = begin->next;
        --index;
    }
    if (index == 1)
    {
        IntList1D_element *temp = new IntList1D_element(number, begin->next);
        begin->next = temp;

        return true;
    }
    else
        return false;
}

/**
 * @brief Cutting list
 * 
 * @param list list, will be cut in range [start;index]
 * @param from start (index)
 * If:  -1    function abort;
 * @param to end (index).
 * If:  0     list cutting to end
 *      -1    function abort;
 * @return IntList1D sublist
 */
IntList1D cutByIndexRange(IntList1D &list, int from, int to)
{
    try
    {
        if (from > to && to != 0)
            throw "cut(): Incorrect couple 'from - to' for cutting list";
        if (from == -1 || to == -1)
            throw "cut(): special argument (-1) given, abort";
    }
    catch (const char *message)
    {
        std::cerr << message << '\n';
        return nullptr;
    }

    IntList1D sublist = new IntList1D_element *;
    *sublist = new IntList1D_element;
    IntList1D_element *list_ptr = *list;

    for (int i = 0; i < from - 1; ++i)
    {
        if (list_ptr->next == nullptr)
            break;
        list_ptr = list_ptr->next;
    }
    IntList1D_element *begin_slice = list_ptr;

    if (to == 0)
        to = INT16_MIN + from;
    for (int i = 0; i < from - to + 1; ++i)
    {
        if (list_ptr->next == nullptr)
            break;
        list_ptr = list_ptr->next;
    }

    IntList1D_element *end_slice = list_ptr->next;

    APPEND_BACK_Link(*sublist, begin_slice->next);

    begin_slice->next = end_slice;
    list_ptr->next = nullptr;

    IntList1D_element *empty = *sublist, *begin = (*sublist)->next;
    delete empty;
    *sublist = begin;

    return sublist;
}

int findFirstOf(const IntList1D list, int number)
{
    IntList1D_element *list_ptr = *list;
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

/**
 * @brief Get the Indexes By field Data of list
 * 
 * @param list list for search data
 * @param data 
 * @return IntList1D list of indexes
 */
IntList1D getIndexesByData(const IntList1D list, int data)
{
    IntList1D_element *list_ptr = *list;
    IntList1D indexes = nullptr;
    int index = 0;
    while (list_ptr != nullptr)
    {
        if (list_ptr->data == data)
            pushBack(indexes, index);
        list_ptr = list_ptr->next;
        ++index;
    }
    return indexes;
}

void doActionOnIndexes(IntList1D list, const IntList1D indexes, void index_action(IntList1D_element *prev, IntList1D_element *current))
{
    IntList1D_element *current = *list, *prev = nullptr;
    IntList1D_element *indexes_ptr = *indexes;

    int index = 0;
    while (current != nullptr && indexes_ptr != nullptr)
    {
        if (indexes_ptr->data == index)
        {
            index_action(prev, current);
            indexes_ptr = indexes_ptr->next;
        }
        prev = current;
        current = current->next;
        ++index;
    }
}

void doActionOnIndexes(IntList1D list, const IntList1D indexes, void index_action(IntList1D_element **prev, IntList1D_element **current, int data), int index_action_data)
{
    IntList1D_element *current = *list, *prev = nullptr;
    IntList1D_element *indexes_ptr = *indexes;

    int index = 0;
    while (current != nullptr && indexes_ptr != nullptr)
    {
        if (indexes_ptr->data == index)
        {
            index_action(&prev, &current, index_action_data);
            indexes_ptr = indexes_ptr->next;
        }
        prev = current;
        current = current->next;
        ++index;
    }
}

void pushBack(IntList1D &list, int number)
{
    if (list == nullptr || *list == nullptr)
        init(list, number);
    else
        PUSH_Back(*list, number);
}

void pushBack(IntList1D &list, IntList1D_element *element)
{
    if (list == nullptr || *list == nullptr)
        init(list, element);
    else
        PUSH_Back(*list, element);
}

void pushFront(IntList1D &list, int number)
{
    if (list == nullptr || *list == nullptr)
        init(list, number);
    else
        PUSH_Front(*list, number);
}

IntList1D_element *popBack(IntList1D &list)
{
    if (list != nullptr && *list == nullptr)
        return POP_Back(*list);
    else
        return nullptr;
}

IntList1D_element *popFront(IntList1D &list)
{
    if (list != nullptr && *list != nullptr)
    {
        IntList1D_element *pop = *list;
        *list = pop->next;
        return pop;
    }
    else
        return nullptr;
}

IntList1D popByIndexes(IntList1D list, const IntList1D indexes)
{
    IntList1D_element *current = *list, *prev = nullptr;
    IntList1D_element *indexes_ptr = *indexes;
    IntList1D deletedElements = nullptr;
    int index = 0;
    while (current != nullptr && indexes_ptr != nullptr)
    {
        if (indexes_ptr->data == index)
        {
            pushBack(deletedElements, current);
            if (prev == nullptr)
            {
                *list = (*list)->next;
                prev = nullptr;
                current->next = nullptr;
                current = *list;
            }
            else
            {
                IntList1D_element *tmp = current->next;
                prev->next = tmp;
                current->next = nullptr;
                current = tmp;
            }
            indexes_ptr = indexes_ptr->next;
        }
        else
        {
            prev = current;
            current = current->next;
        }

        ++index;
    }
    return deletedElements;
}

void deleteList(intList2D list)
{
    if (list != nullptr)
    {
        if (*list != nullptr)
        {
            DEL(*list);
            *list = nullptr;
        }
        delete list;
    }
}

void deleteList(IntList1D list)
{
    if (list != nullptr)
    {
        if (*list != nullptr)
        {
            DEL(*list);
            *list = nullptr;
        }
        delete list;
    }
}

IntList1D reverse(const IntList1D source)
{
    if (is_inited(source))
    {
        IntList1D rotated = nullptr;
        IntList1D_element *begin = *source;
        while (begin != nullptr)
        {
            pushFront(rotated, begin->data);
            begin = begin->next;
        }
        return rotated;
    }
    return nullptr;
}

IntList1D filter(const IntList1D source, bool comparator(int))
{
    if (is_inited(source))
    {
        IntList1D filtered = nullptr;
        IntList1D_element *current = *source;
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

IntList1D filter(const IntList1D source, bool comparator(int, int), int comparator_data)
{
    if (is_inited(source))
    {
        IntList1D filtered = nullptr;
        IntList1D_element *current = *source;
        int current_data;

        while (current != nullptr)
        {
            current_data = current->data;
            if (comparator(current_data, comparator_data))
                pushBack(filtered, current_data);
            current = current->next;
        }
        return filtered;
    }
    return nullptr;
}

namespace comparator
{
    bool positive(int number) { return number > 0; }
    bool negative(int number) { return number < 0; }
    bool greaterThanData(int number, int data) { return number > data; }
    bool lesserThanData(int number, int data) { return number < data; }

} // namespace comparator

namespace merge_actions
{
    int sum(int a, int b) { return a + b; }
} // namespace merge_actions

namespace index_actions
{
    void pushBefore(IntList1D_element **prev, IntList1D_element **current, int data)
    {
        PUSH_Before(*current, data);
        *current = (*current)->next;
    }
} // namespace index_actions

// ########################################################
// ########################################################
// ########## Private functions ###########################
// ########################################################
// ########################################################

IntList1D GEN_USERINPUT_newline(const uint &buffer_size, bool &printInfo)
{
    if (printInfo)
        std::cout << "[INFO] Entered data must be lesser than " << buffer_size + 1 << "\n";
    std::cout << "Enter list: ";
    std::stringstream stream;

    char *buffer = new char[buffer_size];
    std::cin.getline(buffer, buffer_size);
    stream.str(buffer);
    delete[] buffer;
    return CONV_sstreamToList1D(stream);
}

IntList1D CONV_sstreamToList1D(std::stringstream &sstream)
{
    IntList1D list = nullptr;
    while (!sstream.eof())
    {
        int sstream_data;
        sstream >> sstream_data;
        pushBack(list, sstream_data);
    }
    sstream.clear();
    return list;
}

void APPEND_BACK_Copy(IntList1D_element *end, IntList1D_element *appendList)
{
    while (appendList != nullptr)
    {
        end->next = new IntList1D_element(appendList->data);
        end = end->next;
        appendList = appendList->next;
    }
}

void APPEND_BACK_Link(IntList1D_element *end, IntList1D_element *appendList)
{
    end->next = appendList;
}

void APPEND_FRONT_Link(IntList1D list, IntList1D appendList)
{
    appendBack(appendList, list);
    *list = *appendList;
    delete appendList;
}

void PRINT_begin(const IntList1D_element *begin, bool start)
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

void PRINT_begin(const IntList2D_element *begin, bool start)
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

void PRINT_end(const IntList2D_element *end, bool start)
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

void DEL(IntList1D_element *begin)
{
    IntList1D_element *prev = begin, *temp = begin->next;
    while (temp != nullptr)
    {
        delete prev;
        prev = temp;
        temp = temp->next;
    }
    delete prev;
    begin = nullptr;
}

void DEL(IntList2D_element *begin)
{
    IntList2D_element *prev = begin, *temp = begin->next;
    while (temp != nullptr)
    {
        delete prev;
        prev = temp;
        temp = temp->next;
    }
    delete prev;
    begin = nullptr;
}

bool PUSH_Before(IntList1D_element *current, int number)
{
    if (current != nullptr)
    {
        IntList1D_element *temp = new IntList1D_element(current->data, current->next);
        current->data = number;
        current->next = temp;

        return true;
    }
    else
        return false;
}

void PUSH_Back(IntList1D_element *begin, int number)
{
    while (begin->next != nullptr)
    {
        begin = begin->next;
    }
    begin->next = new IntList1D_element(number);
}

void PUSH_Back(IntList1D_element *begin, IntList1D_element *element)
{
    while (begin->next != nullptr)
    {
        begin = begin->next;
    }
    begin->next = element;
}

void PUSH_Front(IntList1D_element *begin, int number)
{
    PUSH_Before(begin, number);
}

IntList1D_element *POP_Back(IntList1D_element *begin)
{
    IntList1D_element prev;
    while (begin->next != nullptr)
    {
        prev = *begin;
        begin = begin->next;
    }

    prev.next = nullptr;
    return begin;
}

bool INS_UpperSortedCycle(IntList1D_element *current, int number)
{
    while (current->next != nullptr && current->data <= number)
        current = current->next;

    if (current->data > number)
        return PUSH_Before(current, number);

    else if (current->next == nullptr)
    {
        PUSH_Back(current, number);
        return true;
    }

    return false;
}

bool INS_UpperSortedRecursion(IntList1D_element *current, int number)
{
    if (current->data > number)
        return PUSH_Before(current, number);

    else if (current->next == nullptr)
    {
        PUSH_Back(current, number);
        return true;
    }

    else
        return INS_UpperSortedRecursion(current->next, number);
}