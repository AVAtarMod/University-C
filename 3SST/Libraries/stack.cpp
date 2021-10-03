#include "stack.hpp"

bool empty(stack stack_data)
{
    return (stack_data != nullptr && *stack_data != nullptr);
}

stack_element *pop(stack &stack_data)
{
    if (!empty(stack_data))
    {
        stack_element *first = *stack_data;
        *stack_data = first->next;
        return first;
    }
}

stack_element *push(stack &stack_data)
{
    if (!empty(stack_data))
    {
        stack_element *first = *stack_data;
        *stack_data = first->next;
        return first;
    }
}