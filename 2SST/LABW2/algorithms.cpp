#include <cstring>
#include <vector>
#include <string>

#include "algorithms.hpp"
#include "TextTable.h"

Data linearAccelerated(const char *string, const char *search)
{
    Data result(false, -1, 0);
    uint16_t searchLength = strlen(search), i = 0;
    int indexString = -1;
    for (uint16_t s = 0; s < strlen(string) && i < searchLength; s++)
    {
        result.numberComparisons++;
        if (string[s] == search[i])
        {
            i++;
            if (i == 1)
                indexString = s;
        }
        else
            i = 0;
    }
    if (i == searchLength)
    {
        result.stringWasFound = true;
        result.indexString = indexString;
    }
    return result;
}

Data linear(const char *string, const char *search)
{
    Data result(false, -1, 0);
    uint16_t searchLength = strlen(search), i = 0;
    uint64_t stringLength = strlen(string);
    int indexString = -1;
    for (uint16_t s = 0; s <= stringLength - searchLength && i != searchLength; s++)
    {
        i = 0;
        while (i < searchLength && string[s + i] == search[i])
        {
            result.numberComparisons++;
            i++;
            if (i == 1)
                indexString = s;
        }
    }
    if (i == searchLength)
    {
        result.stringWasFound = true;
        result.indexString = indexString;
    }
    return result;
}

Data boyerMoor(const char *search)
{
    Data result(false, -1, 0);
    uint16_t searchLength = strlen(search), c = 1;
    std::vector<std::pair<int, std::string>> table(searchLength);
    table[searchLength - 1u].second = search[searchLength - 1];
    std::cout << "\n\nStages:\n";
    for (int i = searchLength - 2; i >= 0; i--)
    {
        table[static_cast<uint32_t>(i)].first = c;
        table[static_cast<uint32_t>(i)].second = search[i];
        c++;
    }

    TextTable stage;
    stage.add("");
    for (auto i : table)
        stage.add(i.second);
    stage.endOfRow();
    stage.add("Stage 1");
    for (auto i : table)
        stage.add(std::to_string(i.first));
    stage.endOfRow();

    std::string charLast;
    charLast = search[searchLength - 1];

    bool lastCharIsDuplicated = false;
    for (int i = searchLength - 2; i >= 0; i--)
    {
        std::string charComparison = table[static_cast<uint32_t>(i)].second;
        int intComparison = table[static_cast<uint32_t>(i)].first;
        for (int b = i - 1; b >= 0; b--)
        {
            if (table[static_cast<uint32_t>(b)].second == charComparison)
                table[static_cast<uint32_t>(b)].first = intComparison;
        }
        if (charComparison == charLast)
        {
            table[searchLength - 1u].first = table[static_cast<uint32_t>(i)].first;
            lastCharIsDuplicated = true;
        }
    }
    if (!lastCharIsDuplicated)
        table[searchLength - 1u].first = searchLength;

    stage.add("Stage 2");
    for (auto i : table)
        stage.add(std::to_string(i.first));
    stage.endOfRow();
    std::cout << stage;

    return result;
}

/* Data knuthMorisPratt(const char *string, const char *search)
{
}

Data rabinKarp(const char *string, const char *search)
{
} */

std::ostream &operator<<(std::ostream &out, Data data)
{
    out << std::boolalpha << data.stringWasFound << " number comparisons: " << data.numberComparisons << " index string: " << data.indexString << std::endl;
    return out;
}
