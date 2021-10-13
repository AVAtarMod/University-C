#ifndef QUERY_LIB
#define QUERY_LIB

#include "list.hpp"

template <class T>
struct Queue
{
    List1D<T> list;
    List1D_element<T> *begin;
    List1D_element<T> *end;
    Queue() : list(nullptr),
              begin(nullptr),
              end(nullptr){};
};

typedef Queue<int> IntQueue;
typedef IntList1D_element IntQueue_element;

template <class T>
using Queue_element = List1D_element<T>;

template <class T>
bool isEmpty(Queue<T> queue)
{
    return (queue.list == nullptr || *queue.list == nullptr);
}

template <class T>
Queue_element<T> *pop(Queue<T> &queue)
{
    return popBack(queue);
}

template <class T>
void deleteQueue(Queue<T> &queue)
{
    deleteList(queue.list);
    queue.begin = nullptr;
    queue.end = nullptr;
}

template <class T>
void push(Queue<T> &queue, T data)
{
    pushFront(queue, data);
}

template <class T>
void updateFields(Queue<T> &queue)
{
    queue.begin = *(queue.list);
    Queue_element<T> *tmp = queue.begin;
    if (tmp != nullptr)
    {
        while (tmp->next != nullptr)
            tmp = tmp->next;

        queue.end = tmp;
    }
    else
    {
        queue.end = queue.begin;
    }
}

#endif //QUERY_LIB
