#include "LW_lib.hpp"

IntList1D checkBraces(const std::string braces, const std::string strWithBraces)
{
    const int DEFAULT_VALUE = 0;

    Stack<int> open_braces = nullptr;
    Stack<int> closed_braces = nullptr;
    IntList1D invalidIdx = nullptr;
    const uint strLen = strWithBraces.size();

    for (uint16_t i = 0; i < strLen; ++i)
    {
        char current = strWithBraces[i];
        const uint64_t bracesIdx = braces.find_first_of(current);
        if (bracesIdx != braces.npos)
        {
            if (bracesIdx % 2 == 0)
                push(open_braces, static_cast<int>(i));
            else
                push(closed_braces, static_cast<int>(i));
        }
    }
    while (!isEmpty(open_braces) || !isEmpty(closed_braces))
    {
        Stack_element<int> *curOpen = pop(open_braces);
        Stack_element<int> *curClosed = pop(closed_braces);
        bool isError =
            curOpen == nullptr ||
            curClosed == nullptr ||
            (curOpen->data > curClosed->data);
        if (isError)
            pushBack(invalidIdx, DEFAULT_VALUE);

        if (curOpen != nullptr)
            delete curOpen;
        if (curClosed != nullptr)
            delete curClosed;
    }

    if (invalidIdx != nullptr)
        appendBack(invalidIdx, mergeUpperSorted(open_braces, closed_braces, true));
    return invalidIdx;
}