#ifndef QUERY_LIB
#define QUERY_LIB

#include "list.hpp"

struct query
{
    intList1D list;
    IntList1D_element *begin;
    IntList1D_element *end;
};

typedef IntList1D_element query_element;

#endif //QUER_LIB