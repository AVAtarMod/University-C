#include "algorithms.hpp"

Data simpleSelection(int *ar, uint32_t ln)
{
    Data result;
    for (uint32_t i = 0; i < ln - 1; i++)
    {
        int min = INT32_MAX;
        uint32_t iMin;
        for (uint32_t iInner = i; iInner < ln;
             iInner++, result.comparisons++)
            if (ar[iInner] < min)
                min = ar[iInner], iMin = iInner;

        std::swap(ar[i], ar[iMin]);
        result.replaces++;
    }
    return result;
}

Data simpleExchange(int *ar, uint32_t ln)
{
    Data result;
    uint32_t currentState = 1;
    while (result.replaces != currentState)
    {
        currentState = result.replaces;
        for (uint16_t i = 0; i < ln - 1; i++)
        {
            if (ar[i] > ar[i + 1])
            {
                std::swap(ar[i], ar[i + 1]);
                result.replaces++;
            }
            result.comparisons++;
        }
    }
    return result;
}

Data simpleExchangeImproved(int *ar, uint32_t ln)
{
    Data result;
    uint32_t currentState = 1, iLastReplace = ln;
    bool isWasLastPass = false;
    while (result.replaces != currentState && !isWasLastPass)
    {
        currentState = result.replaces;
        for (uint16_t i = 0; i < iLastReplace - 1; i++)
        {
            if (ar[i] > ar[i + 1])
            {
                std::swap(ar[i], ar[i + 1]);
                result.replaces++;
                iLastReplace = i + 1;
            }
            result.comparisons++;
        }
        if (ln == iLastReplace)
            isWasLastPass = true;
    }
    return result;
}

Data shakerSort(int *ar, uint32_t ln)
{
    Data result;
    long border = ln;
    uint32_t left = 0;
    long right = ln - 1;
    do
    {
        for (long i = left; i < right; i++)
        {
            result.comparisons++;
            if (ar[i] > ar[i + 1])
            {
                result.replaces++;
                std::swap(ar[i], ar[i + 1]);
                border = i;
            }
        }
        right = border;
        for (long i = right; i > left; i--)
        {
            result.comparisons++;
            if (ar[i] < ar[i - 1])
            {
                result.replaces++;
                std::swap(ar[i], ar[i + 1]);
                border = i;
            }
        }
        left = border;
    } while (left < right);
    return result;
}

Data insertion(int *ar, uint32_t ln)
{
    Data result;
    for (uint32_t i = 1; i < ln; i++)
    {
        int current = ar[i], iInsert;
        bool stop = false;

        for (long ii = i - 1; ii > 0 && !stop; ii--)
        {
            result.comparisons++;
            if (ar[ii] > current)
            {
                iInsert = ii;
                stop = true;
            }
        }

        std::swap(ar[i], ar[iInsert]);
        result.replaces++;
    }
    return result;
}