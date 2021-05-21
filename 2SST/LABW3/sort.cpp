#include "sort.hpp"

Data simpleSelection(int *ar, uint ln)
{
    Data result;
    for (uint i = 0; i < ln - 1; i++)
    {
        int min = INT32_MAX;
        uint iMin;
        for (uint iInner = i; iInner < ln;
             iInner++, result.comparisons++)
            if (ar[iInner] < min)
                min = ar[iInner], iMin = iInner;

        std::swap(ar[i], ar[iMin]);
        result.replaces++;
    }
    return result;
}

Data simpleExchange(int *ar, uint ln)
{
    Data result;
    uint currentState = 1;
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

Data simpleExchangeImproved(int *ar, uint ln)
{
    Data result;
    uint currentState = 1, iLastReplace = ln;
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

Data shakerSort(int *ar, uint ln)
{
    Data result;
    long current, control, left = 0, right = ln - 1;
    do
    {
        for (int i = left; i < right; i++)
        {
            if (ar[i] > ar[i + 1])
            {
                current = ar[i];
                ar[i] = ar[i + 1];
                ar[i + 1] = current;
                control = i;
            }
        }
        right = control;
        for (int i = right; i > left; i--)
        {
            if (ar[i] < ar[i - 1])
            {
                current = ar[i];
                ar[i] = ar[i - 1];
                ar[i - 1] = current;
                control = i;
            }
        }
        left = control;
    } while (left < right);

    return result;
}

void doInsert(int *ar, uint ln, uint iFrom, uint iTo)
{
    if (iFrom > iTo && iTo < ln - 1 && iFrom < ln)
    {
        int buffer = ar[iFrom];
        for (uint i = iFrom; i != iTo; --i)
            ar[i] = ar[i - 1];

        ar[iTo] = buffer;
    }
}

Data insertion(int *ar, uint ln)
{
    Data result;

    for (uint i = 1; i < ln; i++)
    {
        int current = ar[i];
        long ii = i - 1;
        for (; ii >= 0 && ar[ii] > current; --ii)
        {
            result.comparisons++;
            result.replaces++;
        }
        doInsert(ar, ln, i, ii + 1);
    }
    return result;
}

Data insertionImproved(int *ar, uint ln)
{
    Data result;
    int *arResult = new int[ln + 1];
    for (uint i = 1; i < ln; i++)
        arResult[i] = ar[i - 1];

    for (uint i = 1; i < ln + 1; i++)
    {
        long ii = i - 1;
        arResult[0] = arResult[i];
        for (; arResult[ii] > arResult[i]; --ii)
        {
            result.comparisons++;
            result.replaces++;
            arResult[ii + 1] = arResult[ii];
        }
        arResult[ii + 1] = arResult[0];
    }

    for (uint i = 0; i < ln; i++)
        ar[i] = arResult[i + 1];

    delete[] arResult;

    return result;
}

uint quickSortPartition(int *ar, uint left, uint right, uint data[2])
{
    int pivot = ar[left];
    int i = static_cast<int>(left - 1), j = static_cast<int>(right + 1);

    while (true)
    {
        // Find leftmost element greater than
        // or equal to pivot
        do
        {
            i++, data[1]++;
        } while (ar[i] < pivot);

        // Find rightmost element smaller than
        // or equal to pivot
        do
        {
            j--, data[1]++;
        } while (ar[j] > pivot);

        // If two pointers met.
        if (i >= j)
            return static_cast<uint>(j);

        std::swap(ar[i], ar[j]),data[0]++;
    }
}

void quickSortRecursive(int *ar, uint left, uint right, uint data[2])
{
    while (left < right)
    {
        uint middle = quickSortPartition(ar, left, right, data);
        quickSortRecursive(ar, left, middle, data);
        quickSortRecursive(ar, middle + 1u, right, data);
    }
}

Data quickSort(int *ar, uint ln)
{
    uint data[2]{0};
    quickSortRecursive(ar, 0, ln - 1, data);
    return Data{data[0], data[1]};
}