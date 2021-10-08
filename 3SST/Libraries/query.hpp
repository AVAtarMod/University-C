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
    return popBack(query);
}

template <class T>
void push(Query<T> &query, T data)
{
    pushFront(query, data);
}

#endif //QUERY_LIB