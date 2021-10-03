#include "stack.hpp"

bool empty(Stack stack_data)
{
    return (stack_data != nullptr && *stack_data != nullptr);
}

Stack_element *pop(Stack &stack_data)
{
    return popFront(stack_data);
}

void push(Stack &stack, int data)
{
    pushFront(stack, data);
}