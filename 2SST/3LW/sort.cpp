#include "sort.hpp"

enum quickSortParts {
    LESSER_THAN_MIDDLE,
    EQUAL,
    GREATER_THAN_MIDDLE
};

Data simpleSelection(int* array, uint length)
{
    Data result;
    for (uint i = 0; i < length - 1; i++) {
        int min = INT32_MAX;
        uint iMin;
        for (uint iInner = i; iInner < length;
             iInner++, result.comparisons++)
            if (array[iInner] < min)
                min = array[iInner], iMin = iInner;

        std::swap(array[i], array[iMin]);
        result.replaces++;
    }
    return result;
}

Data simpleExchange(int* array, uint length)
{
    Data result;
    uint currentState = 1;
    while (result.replaces != currentState) {
        currentState = result.replaces;
        for (uint16_t i = 0; i < length - 1; i++) {
            if (array[i] > array[i + 1]) {
                std::swap(array[i], array[i + 1]);
                result.replaces++;
            }
            result.comparisons++;
        }
    }
    return result;
}

Data simpleExchangeImproved(int* array, uint length)
{
    Data result;
    uint currentState = 1, iLastReplace = length;
    bool isWasLastPass = false;
    while (result.replaces != currentState && !isWasLastPass) {
        currentState = result.replaces;
        for (uint16_t i = 0; i < iLastReplace - 1; i++) {
            if (array[i] > array[i + 1]) {
                std::swap(array[i], array[i + 1]);
                result.replaces++;
                iLastReplace = i + 1;
            }
            result.comparisons++;
        }
        if (length == iLastReplace)
            isWasLastPass = true;
    }
    return result;
}

Data shakerSort(int* array, uint length)
{
    Data result;
    long control, left = 0, right = length - 1;
    do {
        for (int i = left; i < right; i++) {
            ++result.comparisons;
            if (array[i] > array[i + 1]) {
                ++result.replaces;
                std::swap(array[i], array[i + 1]);
                control = i;
            }
        }
        right = control;
        for (int i = right; i > left; i--) {
            ++result.comparisons;
            if (array[i] < array[i - 1]) {
                ++result.replaces;
                std::swap(array[i], array[i - 1]);
                control = i;
            }
        }
        left = control;
    } while (left < right);

    return result;
}

void doInsert(int* array, uint length, uint iFrom, uint iTo, uint offset = 0)
{
    if (iFrom > iTo && iTo < length - 1 && iFrom < length) {
        int buffer = array[iFrom];
        for (uint i = iFrom; i != iTo && i >= offset; --i)
            array[i] = array[i - 1];

        array[iTo] = buffer;
    }
}

Data insertion(int* array, uint length)
{
    Data result;

    for (uint i = 1; i < length; i++) {
        int current = array[i];
        long ii = i - 1;
        for (; ii >= 0 && array[ii] > current; --ii) {
            result.comparisons++;
            result.replaces++;
        }
        doInsert(array, length, i, ii + 1);
    }
    return result;
}

Data insertionImproved(int* array, uint length)
{
    Data result;
    int* arResult = new int[length + 1];
    for (uint i = 1; i < length; i++)
        arResult[i] = array[i - 1];

    for (uint i = 2; i < length + 1; i++) {
        long ii = i - 1;
        arResult[0] = arResult[i];
        for (; arResult[ii] > arResult[0]; --ii) {
            result.comparisons++;
            result.replaces++;
            array[ii + 1] = array[ii];
        }
        array[ii + 1] = array[0];
    }

    int buffer = array[length - 1];
    for (uint i = 0; i < length; i++)
        array[i] = arResult[i + 1];

    delete[] arResult;
    if (array[length - 1] < array[length - 2]) {
        std::swap(array[length - 1], array[length - 2]);
        if (array[length - 2] < array[0])
            std::swap(array[length - 2], array[0]);
    }
    array[length - 2] = buffer;
    return result;
}

/**
 * @param array array
 * @param left left limit (first index)
 * @param right right limit (last index + 1)
 * @param data [numberReplaces, numberComparisons]
 */
void quickSortRecursive(int* array, uint left, uint right, uint data[2])
{
    if (right - left > 1) {
        const int amountParts = 3;
        int* parts[amountParts];
        for (unsigned i = 0; i < amountParts; i++)
            parts[i] = new int[right - left - 1];

        uint middle = left + right / 2;

        /**
         * @brief Lengths of parts for LESSER_THAN_MIDDLE,
         * EQUAL, GREATER_THAN_MIDDLE
         */
        uint ip1 = 0, ip2 = 0, ip3 = 0;
        for (unsigned i = left; i < right; i++) {
            if (array[i] < array[middle]) {
                if (i > middle)
                    ++data[0], data[1] += 1;
                parts[LESSER_THAN_MIDDLE][ip1] = array[i];
                ++ip1;
            } else if (array[i] == array[middle]) {
                if (i != middle)
                    ++data[0], data[1] += 2;
                parts[EQUAL][ip2] = array[i];
                ++ip2;
            } else if (array[i] > array[middle]) {
                if (i < middle)
                    ++data[0], data[1] += 2;
                parts[GREATER_THAN_MIDDLE][ip3] = array[i];
                ++ip3;
            }
        }

        try {
            if (ip1 + ip2 + ip3 != right - left) {
                for (unsigned i = 0; i < amountParts; i++)
                    delete[] parts[i];
                throw ip1 + ip2 + ip3;
            }
        } catch (int err) {
            std::cerr << err << " not equal " << right - left << "!\n";
        }

        unsigned iAr = left;
        for (unsigned i = 0; i < ip1; i++, iAr++)
            array[iAr] = parts[LESSER_THAN_MIDDLE][i];

        for (unsigned i = 0; i < ip2; i++, iAr++)
            array[iAr] = parts[EQUAL][i];

        for (unsigned i = 0; i < ip3; i++, iAr++)
            array[iAr] = parts[GREATER_THAN_MIDDLE][i];

        for (unsigned i = 0; i < amountParts; i++)
            delete[] parts[i];

        if (ip1 > 1)
            quickSortRecursive(array, left, ip1, data);
        if (ip3 > 1)
            quickSortRecursive(array, ip1 + ip2, right, data);
    }
}

Data quickSort(int* array, uint length)
{
    uint data[2] { 0 };
    quickSortRecursive(array, 0, length, data);
    return Data { data[0], data[1] };
}

void mergeRecursive(int* array, uint left, uint right, uint data[2])
{
    if (right - left > 2) {
        uint middle = (left + right) / 2;
        mergeRecursive(array, left, middle, data);
        mergeRecursive(array, middle, right, data);

        int* tempArray = new int[right - left];
        for (unsigned iL = left, iR = middle, iTmp = 0; iR < right; ++iL, ++iR, iTmp += 2) {
            if (array[iL] <= array[iR]) {
                ++data[0], ++data[1];
                tempArray[iTmp] = array[iL];
                tempArray[iTmp + 1] = array[iR];
            }

            else if (array[iL] > array[iR]) {
                ++data[0], ++data[1];
                tempArray[iTmp] = array[iR];
                tempArray[iTmp + 1] = array[iL];
            }
        }
        for (unsigned i = left; i < right; ++i)
            array[i] = tempArray[i - left];

        delete[] tempArray;
    } else if (right - left == 2) {
        if (array[left] > array[right - 1])
            std::swap(array[left], array[right - 1]);
    }
}

Data merge(int* array, uint length)
{
    uint data[2] { 0 };
    mergeRecursive(array, 0, length, data);
    return Data { data[0], data[1] };
}