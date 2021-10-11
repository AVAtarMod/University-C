#ifndef QUERY_LIB
#define QUERY_LIB

#include "list.hpp"

template <class T>
struct Queue
{
    List1D<T> list;
    List1D_element<T> *begin;
    List1D_element<T> *end;
};

typedef Queue<int> IntQueue;
typedef IntList1D_element IntQueue_element;

template <class T>
using Queue_element = List1D_element<T>;

template <class T>
bool isEmpty(Queue<T> query)
{
    return (query.list == nullptr || *query.list == nullptr);
}

template <class T>
Queue_element<T> *pop(Queue<T> &query)
{
    return popBack(query);
}

template <class T>
void push(Queue<T> &query, T data)
{
    pushFront(query, data);
}

#endif //QUERY_LIB
