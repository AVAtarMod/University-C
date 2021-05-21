#ifndef labw3algo
#define labw3algo

#include <iostream>

#include "Data.hpp"

Data simpleSelection(int *array, uint32_t length);
Data simpleExchange(int *ar, uint32_t length);

Data simpleExchangeImproved(int *ar, uint32_t ln);
Data shakerSort(int *ar, uint32_t ln);

Data insertion(int *ar, uint32_t ln);
Data insertionImproved(int *ar, uint32_t ln);

Data quickSort(int *ar, uint32_t ln);

#endif