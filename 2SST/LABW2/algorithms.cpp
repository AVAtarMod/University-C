#include <cstring>
#include <algorithm>

#include "algorithms.hpp"
#include "TextTable.hpp"

#define cast static_cast

Data linearAccelerated(const char *string, const char *search)
{
    Data result(false, -1, 0);
    uint16_t searchLength = strlen(search), i = 0;
    int indexString = -1;
    for (uint16_t s = 0;
         s < strlen(string) &&
         i != searchLength - 1;
         s++)
    {
        result.numberComparisons++;
        if (string[s] != search[i] || i > searchLength - 1)
            i = 0;
        if (string[s] == search[i])
        {
            i++;
            if (i == 1)
                indexString = s;
        }
    }
    if (i == searchLength - 1)
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
    int indexString;
    for (long s = 0; s <= cast<int>(stringLength - searchLength) && i != searchLength; s++)
    {
        i = 0;
        result.numberComparisons++;
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

Data boyerMoor(const char *string, const char *search)
{
    Data result(false, -1, 0);
    uint16_t searchLength = strlen(search), c = 1;
    uint64_t stringLength = strlen(string);
    if (stringLength >= searchLength)
    {
        std::vector<std::pair<int, std::string>> table(searchLength);
        table[searchLength - 1u].second = search[searchLength - 1];

        for (int i = searchLength - 2; i >= 0; i--)
        {
            table[cast<uint32_t>(i)].first = c;
            table[cast<uint32_t>(i)].second = search[i];
            c++;
        }

        std::string charLast = {search[searchLength - 1]};
        bool lastCharAlone = true;
        for (int i = searchLength - 2; i >= 0; i--)
        {
            std::string charComparison = table[cast<uint32_t>(i)].second;
            int intComparison = table[cast<uint32_t>(i)].first;
            for (int b = i - 1; b >= 0; b--)
            {
                if (table[cast<uint32_t>(b)].second == charComparison)
                    table[cast<uint32_t>(b)].first = intComparison;
            }
            if (charComparison == charLast)
            {
                table[searchLength - 1u].first = table[cast<uint32_t>(i)].first;
                lastCharAlone = false;
            }
        }

        if (lastCharAlone)
            table[searchLength - 1u].first = searchLength;

        for (int iStr = searchLength, iSearch;
             iStr <= cast<int>(stringLength) && !result.stringWasFound;)
        {
            iSearch = searchLength;
            result.numberComparisons++;
            for (int iStrRev = iStr;
                 iSearch != 0 &&
                 string[iStrRev - 1] == search[iSearch - 1];)
            {
                result.numberComparisons++;
                --iStrRev;
                --iSearch;
            }
            if (iSearch == 0)
            {
                result.indexString = iStr - 1;
                result.stringWasFound = true;
            }
            else
            {
                std::string needFind = {string[iStr - 1]};
                auto pos = std::find_if(
                    table.begin(),
                    table.end(),
                    [needFind](const std::pair<int, std::string> &x) { return (x.second == needFind); });
                if (pos == table.end())
                    iStr += searchLength;
                else
                    iStr += pos->first;
            }
        }
    }
    return result;
}

Data knuthMorisPratt(const char *string, const char *search)
{
    Data result(false, -1, 0);
    uint16_t searchLength = strlen(search);
    uint64_t stringLength = strlen(string);
    std::vector<uint32_t> prefix(searchLength);

    prefix[0] = 0;
    for (uint16_t right = 1, left = 0; right < searchLength; right++)
    {
        if (search[right] != search[left])
        {
            if (left == 0)
                prefix[right] = 0;
            else
                left = prefix[left - 1];
        }
        if (search[right] == search[left])
        {
            prefix[right] = left + 1;
            left++;
        }
    }
    for (auto &&i : prefix)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (uint64_t iStart = 0, iStr = 0, iSearch = 0;
         iStr < stringLength && !result.stringWasFound;
         iStr++)
    {
        result.numberComparisons++;
        if (string[iStr] != search[iSearch])
            iSearch = prefix[iSearch - 1];
        if (string[iStr] == search[iSearch])
        {
            if (iSearch == 0)
                iStart = iStr;
            if (iSearch == cast<uint64_t>(searchLength - 1))
            {
                result.stringWasFound = true;
                result.indexString = iStart;
            }
            iSearch++;
        }
    }

    return result;
}

long hash(const char *string, int length)
{
    long hash_number = 0;
    for (uint16_t i = 0; i < length; i++)
        hash_number += cast<long>(string[i]);
    return hash_number;
}

Data rabinKarp(const char *string, const char *search)
{
    Data result(false, -1, 0);
    uint16_t searchLength = strlen(search);
    uint64_t stringLength = strlen(string);
    long hashSearch = hash(search, searchLength);

    for (uint16_t i = 0; i < stringLength - searchLength + 1 && !result.stringWasFound; i++)
    {
        result.numberComparisons++;
        if (hash(string + i, searchLength) == hashSearch &&
            strncmp(string + i, search, searchLength) == 0)
        {
            result.numberComparisons += searchLength;
            result.indexString = i;
            result.stringWasFound = true;
        }
    }

    return result;
}

std::ostream &operator<<(std::ostream &out, Data data)
{
    out << std::boolalpha << data.stringWasFound << " number comparisons: " << data.numberComparisons << " index string: " << data.indexString << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, std::vector<std::pair<int, std::string>> array)
{
    TextTable table;

    for (auto &i : array)
        table.add(std::to_string(i.first));
    table.endOfRow();
    for (auto &i : array)
        table.add(i.second);
    table.endOfRow();
    out << table;

    return out;
}