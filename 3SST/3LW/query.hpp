#ifndef QUERY_LIB
#define QUERY_LIB

#include "list.hpp"

struct query
{
    intList1D list;
    intList1D_element *begin;
    intList1D_element *end;
};

typedef intList1D_element query_element;

#endif //QUER_LIB