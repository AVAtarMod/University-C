#ifndef QUERY_LIB
#define QUERY_LIB

#include "list.hpp"

template <class T>
struct Query
{
    List1D<T> list;
    List1D_element<T> *begin;
    List1D_element<T> *end;
};

typedef Query<int> IntQuery;
typedef IntList1D_element IntQuery_element;

template <class T>
using Query_element = List1D_element<T>;

template <class T>
bool isEmpty(Query<T> query)
{
    return (query.list == nullptr || *query.list == nullptr);
}

template <class T>
Query_element<T> *pop(Query<T> &query)
{
    if (query != nullptr && *query == nullptr)
    {
        Query_element<T> *begin = *query.list;
        Query_element<T> prev;
        while (begin->next != nullptr)
        {
            prev = *begin;
            begin = begin->next;
        }
        prev.next = nullptr;
        return begin;
    }
    else
        return nullptr;
}

template <class T>
void push(Query<T> &query, T data)
{
    pushFront(query, data);
}

#endif //QUERY_LIB