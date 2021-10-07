#ifndef ALGORHITMS
#define ALGORHITMS

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class Data
{
public:
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
    operator std::string()
    {
        std::ostringstream stream;
        stream << std::boolalpha << this->stringWasFound << " " << this->numberComparisons;
        return stream.str();
    }
};

std::ostream &operator<<(std::ostream &out, Data Data);
std::ostream &operator<<(std::ostream &out, std::vector<std::pair<int, std::string>> array);

Data linearAccelerated(const char *string, const char *search);

Data linear(const char *string, const char *search);

Data boyerMoor(const char *string, const char *search);

Data knuthMorisPratt(const char *string, const char *search);

Data rabinKarp(const char *string, const char *search);

#endif