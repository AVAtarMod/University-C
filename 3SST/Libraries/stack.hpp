#ifndef STACK_LIB
#define STACK_LIB

#include "list.hpp"

typedef IntList1D IntStack;
typedef IntList1D_element IntStack_element;

typedef IntList1D_element IntStack_element;

template <class T>
using Stack_element = List1D_element<T>;

template <class T>
using Stack = List1D<T>;

template <class T>
bool isEmpty(Stack<T> stack_data)
{
    return (stack_data == nullptr || *stack_data == nullptr);
}

template <class T>
Stack_element<T> *pop(Stack<T> &stack)
{
    return popFront(stack);
}

template <class T>
void push(Stack<T> &stack, T data)
{
    pushFront(stack, data);
}

template <class T>
void deleteStack(Stack<T> &stack)
{
    deleteList(stack);
}

#endif //STACK_LIB
