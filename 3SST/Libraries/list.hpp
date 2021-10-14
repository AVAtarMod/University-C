#ifndef LIST_LIB
#define LIST_LIB

#include <string>
#include <list>

#include "functions.hpp"

namespace LIST_LIB
{
    const int BUFFER_SIZE = 255;
} // namespace LIST_LIB

template <class T = int>
struct List1D_element
{
    T data;
    List1D_element<T> *next = nullptr;

    List1D_element<T>(){};

    List1D_element(T data, List1D_element<T> *next = nullptr)
        : data(data),
          next(next) {}
};

template <class T = int>
struct List2D_element
{
    List2D_element<T> *previous = nullptr;
    T data;
    List2D_element<T> *next = nullptr;

    List2D_element(List2D_element<T> *previous = nullptr, T data = 0, List2D_element<T> *next = nullptr)
        : previous(previous),
          data(data),
          next(next) {}
};

typedef List1D_element<int> IntList1D_element;
typedef List2D_element<int> IntList2D_element;

typedef IntList1D_element **IntList1D;
typedef IntList2D_element **intList2D;

template <class T>
using List1D = List1D_element<T> **;

enum MODE_STOP
{
    ZERO,
    IO_EOF,
    NEWLINE,
    CHAR,
};
enum FLAGS
{
    USE_CYCLE,
    USE_RECURSION,
};
enum CUT_MODE
{
    CUT_BEFORE,
    CUT_AFTER,
};
enum RETURN_TYPE1D
{
    LIST1D
};
enum RETURN_TYPE2D
{
    LIST2D
};

/**
 * @brief IntList1D functions (non universal)
 */
bool init(IntList1D &list, int number);
bool is_inited(const IntList1D list);

int maxElementData(const intList2D list);
int greaterThenIndex(const intList2D list, int index);
int sumChain(const intList2D list);
int findFirstOf(const IntList1D list, int number);

void deleteList(IntList1D &list);
void deleteList(intList2D list);

void printBegin(const IntList1D list);
void printBegin(const intList2D list);
void printEnd(const intList2D list);

void pushBack(IntList1D &list, int number);
void pushBack(IntList1D &list, IntList1D_element *element);
void pushFront(IntList1D &list, int number);

IntList1D_element *popBack(IntList1D &list);
IntList1D_element *popFront(IntList1D &list);
IntList1D popByIndexes(IntList1D list, const IntList1D indexes);

void appendFront(IntList1D list, IntList1D appendList);
void appendBack(IntList1D &list, IntList1D appendList);

bool insertUpperSorted(IntList1D &begin, int number, FLAGS mode = USE_CYCLE);

IntList1D cutByIndexRange(IntList1D &list, int from, int to);

IntList1D readArrayKeyboard(MODE_STOP mode = IO_EOF, uint buffer_size = UINT8_MAX, bool printInfo = false);
std::list<IntList1D> fileToLists(const std::string filename, const char delimiter = '\n');
IntList1D mergeUpperSorted(IntList1D listA, IntList1D listB, bool listsAlreadySorted = false);
IntList1D mergeByAction(const IntList1D listA, const IntList1D listB, int action(int fromA, int fromB));
IntList1D reverse(const IntList1D source);
IntList1D getIndexesByData(const IntList1D list, int data);

namespace comparator
{
    bool positive(int number);
    bool negative(int number);
    bool greaterThanData(int number, int data);
    bool lesserThanData(int number, int data);
}

namespace merge_actions
{
    int sum(int a, int b);
} // namespace merge_actions

namespace index_actions
{
    void pushBefore(IntList1D_element **prev, IntList1D_element **current, int data);
    void pushAfter(IntList1D_element **prev, IntList1D_element **current, int data);
} // namespace index_actions

IntList1D filter(const IntList1D source, bool comparator(int));
IntList1D filter(const IntList1D source, bool comparator(int, int), int comparator_data);

void doActionOnIndexes(IntList1D list, const IntList1D indexes, void index_action(IntList1D_element *prev, IntList1D_element *current));
void doActionOnIndexes(IntList1D list, const IntList1D indexes, void index_action(IntList1D_element **prev, IntList1D_element **current, int data), int index_action_data);

/**
 * @brief List1D functions (universal templates)
 */

template <class T>
bool init(List1D<T> &list, T data)
{
    if (list == nullptr || *list == nullptr)
    {
        if (list == nullptr)
            list = new List1D_element<T> *;
        *list = new List1D_element<T>(data);
        return true;
    }
    return false;
}

template <class T>
bool init(List1D<T> &list, List1D_element<T> *element)
{
    if (list == nullptr)
    {
        list = new List1D_element<T> *;
        *list = element;
        return true;
    }
    return false;
}

template <class T>
bool is_inited(const List1D<T> list)
{
    if (list == nullptr && *list == nullptr)
        return false;
    else
        return true;
}

template <class T>
uint getLength(const List1D<T> list)
{
    uint length = 0;
    if (list != nullptr && *list != nullptr)
    {
        List1D_element<T> *tmp = *list;
        while (tmp != nullptr)
        {
            tmp = tmp->next;
            ++length;
        }
    }

    return length;
}

template <class T>
List1D_element<T> *popBack(List1D<T> &list)
{
    if (list != nullptr && *list != nullptr)
    {
        List1D_element<T> *begin = *list;
        List1D_element<T> *prev = nullptr;
        while (begin->next != nullptr)
        {
            prev = begin;
            begin = begin->next;
        }

        if (prev != nullptr)
            prev->next = nullptr;
        return begin;
    }
    else
        return nullptr;
}

template <class T>
List1D_element<T> *popFront(List1D<T> &list)
{
    if (list != nullptr && *list != nullptr)
    {
        List1D_element<T> *pop = *list;
        *list = pop->next;
        return pop;
    }
    else
        return nullptr;
}

template <class T>
void pushBack(List1D<T> &list, List1D_element<T> *element)
{
    if (list == nullptr || *list == nullptr)
        init(list, element);
    else
    {
        List1D_element<T> *begin = *list;
        while (begin->next != nullptr)
        {
            begin = begin->next;
        }
        begin->next = element;
    }
}

template <class T>
void pushFront(List1D<T> &list, T data)
{
    if (list == nullptr || *list == nullptr)
        init(list, data);
    else
    {
        List1D_element<T> *current = *list;
        if (current != nullptr)
        {
            List1D_element<T> *temp = new List1D_element<T>(current->data, current->next);
            current->data = data;
            current->next = temp;
        }
    }
}

template <class T>
void deleteList(List1D<T> &list)
{
    if (list != nullptr)
    {
        if (*list != nullptr)
        {
            List1D_element<T> *prev = *list, *temp = (*list)->next;
            while (temp != nullptr)
            {
                delete prev;
                prev = temp;
                temp = temp->next;
            }
            delete prev;
            *list = nullptr;
        }
        delete list;
        list = nullptr;
    }
}

#endif //LIST_LIB
