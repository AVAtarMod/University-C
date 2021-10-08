#include "LW_lib.hpp"

bool checkBraces(const std::string braces, const std::string strWithBraces)
{
    Stack<uint> openBraces = nullptr;
    bool strIsValid = true;

    const uint bracesLen = braces.size();
    const uint strLen = strWithBraces.size();

    for (uint16_t i = 0; i < strLen && strIsValid; ++i)
    {
        char current = strWithBraces[i];
        const uint braceIdx = braces.find_first_of(current);
        if (braceIdx <= bracesLen)
        {
            if (braceIdx % 2 == 0)
                push(openBraces, static_cast<uint>(braceIdx));
            else
            {
                Stack_element<uint> *lastBrace = pop(openBraces);
                bool isError = (lastBrace == nullptr ||
                                lastBrace->data + 1 != braceIdx);
                if (isError)
                    strIsValid = false;
                delete lastBrace;
            }
        }
    }

    if (!isEmpty(openBraces))
    {
        deleteStack(openBraces);
        strIsValid = false;
    }

    return strIsValid;
}