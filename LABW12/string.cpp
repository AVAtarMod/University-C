#include <iostream>

#include "string.h"

namespace cstr
{
    using std::cin;
    using std::cout;

    char *getString(bool isLine)
    {
        char *string = new char[255]();
        if (isLine)
        {
            cout << "Введите строку: ";
            cin.getline(string, 255);
            cin.ignore(INT16_MAX,'\n');      
        }
        else
        {
            cout << "Введите слово/строку без пробелов";
            cin >> string;
            cin.ignore(INT16_MAX,'\n');
        }

        return string;
    }

    int *indexSymbols(char *string, char symbol)
    {
        int newLen = 0;
        int length = string[0];
        for (int iCh = 1; iCh < length; iCh++)
        {
            if (string[iCh] == symbol)
                newLen++;
        }

        int *indexes = new int[newLen + 1];
        indexes[0] = newLen + 1;

        int iIndexes = 1;
        for (int iCh = 1; iCh < length; iCh++)
        {
            if (string[iCh] == symbol)
            {
                indexes[iIndexes] = iCh;
                iIndexes++;
            }
        }

        if (newLen == 0)
        {
            delete[] indexes;
            indexes = nullptr;
        }

        return indexes;
    }

} // namespace cstr
