#ifndef LIST_LIB
#define LIST_LIB

#include <string>
#include <list>

struct intList1D_element
{
    int data;
    intList1D_element *next = nullptr;

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
    IO_EOF
};
enum FLAGS
{
    USE_CYCLE,
    USE_RECURSION
};

void printFromBegin(const intList2D list);
void printFromBegin(const intList1D list);
void printFromEnd(const intList2D list);

std::list<int> readArrayFile(std::string filename);
std::list<int> readArrayKeyboard(MODE_STOP mode = ZERO);

bool insertUpperSorted(intList1D begin, int number, FLAGS mode);

#endif //LIST_LIB