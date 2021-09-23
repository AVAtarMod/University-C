#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

#include <string>
#include <list>

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

enum MODE_STOP
{
    ZERO,
    IO_EOF
};

int getRandomNumber(int from, int to);
int sumChain(intList2D_element *begin);
int maxElementData(intList2D_element *begin);

int greaterThenIndex(intList2D_element *begin, int index);

void printFromBegin(intList2D_element *begin, bool start = true);
void printFromEnd(intList2D_element *end, bool start = true);

void del(intList2D_element *begin);

std::list<int> readArrayFile(std::string filename);
std::list<int> readArrayKeyboard(MODE_STOP mode = ZERO);

#endif //FUNCTIONS_HEADER