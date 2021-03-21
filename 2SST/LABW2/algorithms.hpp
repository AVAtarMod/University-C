#ifndef ALGORHITMS
#define ALGORHITMS

#include <bits/stdint-uintn.h>
#include <iostream>

struct Data
{
    bool stringWasFound;
    int indexString;
    uint32_t numberComparisons;

    Data(bool wasFound = false,
         int iString = -1,
         uint32_t nComparisons = 0)
    {
        stringWasFound = wasFound;
        indexString = iString;
        numberComparisons = nComparisons;
    }
};

std::ostream &operator<<(std::ostream &out,Data Data);
std::istream &operator>>(std::istream &out,Data Data);

Data linearAccelerated(const char *string, const char *search);

Data linear(const char *string, const char *search);

Data boyerMoor(const char *search);

#endif