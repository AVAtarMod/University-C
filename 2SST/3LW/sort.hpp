#ifndef labw3algo
#define labw3algo

#include <iostream>

#include "Data.hpp"

Data simpleSelection(int* array, uint length);
Data simpleExchange(int* array, uint length);

Data simpleExchangeImproved(int* array, uint length);
Data shakerSort(int* array, uint length);

Data insertion(int* array, uint length);
Data insertionImproved(int* array, uint length);

/**
 * @brief recursive algorhitm, divides array into 3 parts:
 * LESSER_THAN_MIDDLE, EQUAL, GREATER_THAN_MIDDLE
 * then merge its in ar
 *
 * @param ar array for sorting
 * @param ln length array
 * @return Data about operations
 */
Data quickSort(int* array, uint length);

Data merge(int* array, uint length);

#endif