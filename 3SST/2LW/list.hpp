#ifndef LIST_LIB
#define LIST_LIB

#include <string>
#include <list>

#include "functions.hpp"

namespace LIST_LIB
{
    const int BUFFER_SIZE = 255;
} // namespace LIST_LIB

struct intList1D_element
{
    int data;
    intList1D_element *next = nullptr;

    intList1D_element(){};

    intList1D_element(int data, intList1D_element *next = nullptr)
    {
        this->data = data;
        this->next = next;
    }
};

struct intList2D_element
{
    intList2D_element *previous = nullptr;
    int data;
    intList2D_element *next = nullptr;

    intList2D_element(intList2D_element *previous = nullptr, int data = 0, intList2D_element *next = nullptr)
    {
        this->previous = previous;
        this->data = data;
        this->next = next;
    }
};

typedef intList1D_element **intList1D;
typedef intList2D_element **intList2D;

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
    USE_RECURSION
};
enum RETURN_TYPE1D
{
    LIST1D
};
enum RETURN_TYPE2D
{
    LIST2D
};

bool init(intList1D &list, int number);
bool is_inited(const intList1D list);

int maxElementData(const intList2D list);
int greaterThenIndex(const intList2D list, int index);
int sumChain(const intList2D list);

void deleteList(intList1D list);
void deleteList(intList2D list);

void printBegin(const intList1D list);
void printBegin(const intList2D list);
void printEnd(const intList2D list);

void pushBack(intList1D &list, int number);
void pushFront(intList1D &list, int number);

void appendFront(intList1D list, intList1D appendList);

bool insertUpperSorted(intList1D &begin, int number, FLAGS mode = USE_CYCLE);
intList1D cut(intList1D &list, int from, int to);

intList1D readArrayKeyboard(MODE_STOP mode = ZERO);
std::list<intList1D> fileToLists(const std::string filename, const char delimiter = '\n');
intList1D mergeUpperSorted(intList1D sortedListA, intList1D sortedListB);
intList1D mergeByAction(const intList1D listA, const intList1D listB, int action(int fromA, int fromB));
intList1D reverse(const intList1D source);

namespace comparator
{
    bool positive(int number);
    bool negative(int number);
}

namespace action
{
    int sum(int a, int b);
} // namespace action

intList1D filter(const intList1D source, bool comparator(int));

#endif //LIST_LIB