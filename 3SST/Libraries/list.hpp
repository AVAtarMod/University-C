#ifndef LIST_LIB
#define LIST_LIB

#include <string>
#include <list>

#include "functions.hpp"

namespace LIST_LIB
{
    const int BUFFER_SIZE = 255;
} // namespace LIST_LIB

struct IntList1D_element
{
    int data;
    IntList1D_element *next = nullptr;

    IntList1D_element(){};

    IntList1D_element(int data, IntList1D_element *next = nullptr)
    {
        this->data = data;
        this->next = next;
    }
};

struct IntList2D_element
{
    IntList2D_element *previous = nullptr;
    int data;
    IntList2D_element *next = nullptr;

    IntList2D_element(IntList2D_element *previous = nullptr, int data = 0, IntList2D_element *next = nullptr)
    {
        this->previous = previous;
        this->data = data;
        this->next = next;
    }
};

typedef IntList1D_element **IntList1D;
typedef IntList2D_element **intList2D;

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

bool init(IntList1D &list, int number);
bool is_inited(const IntList1D list);

int maxElementData(const intList2D list);
int greaterThenIndex(const intList2D list, int index);
int sumChain(const intList2D list);
int findFirstOf(const IntList1D list, int number);

void deleteList(IntList1D list);
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
void appendBack(IntList1D list, IntList1D appendList);

bool insertUpperSorted(IntList1D &begin, int number, FLAGS mode = USE_CYCLE);

IntList1D cutByIndexRange(IntList1D &list, int from, int to);

IntList1D readArrayKeyboard(MODE_STOP mode = IO_EOF, uint buffer_size = UINT8_MAX, bool printInfo = false);
std::list<IntList1D> fileToLists(const std::string filename, const char delimiter = '\n');
IntList1D mergeUpperSorted(IntList1D sortedListA, IntList1D sortedListB);
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
} // namespace index_actions

IntList1D filter(const IntList1D source, bool comparator(int));
IntList1D filter(const IntList1D source, bool comparator(int, int), int comparator_data);

void doActionOnIndexes(IntList1D list, const IntList1D indexes, void index_action(IntList1D_element *prev, IntList1D_element *current));
void doActionOnIndexes(IntList1D list, const IntList1D indexes, void index_action(IntList1D_element **prev, IntList1D_element **current, int data), int index_action_data);

#endif //LIST_LIB