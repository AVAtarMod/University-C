#include <iostream>
#include <cstring>
#include <locale>

#include "string.h"

#define SIZE 255 //Size of c-string and std::string
using std::cin;
using std::cout;

template <class T>
void doChangeCase(T &string, uint8_t choice, uint16_t ln)
{
    switch (choice)
    {
    case 1:
    {
        uint8_t replaces = 0;
        for (uint16_t i = 0; i < ln; i++)
        {
            if (replaces == 0 && isalpha(string[i]))
            {
                string[i] = toupper(string[i]);
                ++replaces;
            }
            else if (isalpha(string[i]))
            {
                string[i] = tolower(string[i]);
            }
        }
    }
    break;
    case 2:
        for (uint16_t i = 0; i < ln; i++)
        {
            string[i] = tolower(string[i]);
        }
        break;

    case 3:
        for (uint16_t i = 0; i < ln; i++)
        {
            string[i] = toupper(string[i]);
        }
        break;

    case 4:
        string[0] = toupper(string[0]);
        for (uint16_t i = 1; i < ln; i++)
        {
            if (string[uint16_t(i - 1)] == ' ' && isalpha(string[i]))
                string[i] = toupper(string[i]);
        }
        break;

    case 5:
        for (uint16_t i = 0; i < ln; i++)
        {
            if (islower(string[i]))
                string[i] = toupper(string[i]);
            else if (isupper(string[i]))
                string[i] = tolower(string[i]);
        }
        break;

    default:
        break;
    }
}

namespace cstr
{

    char *getStringUser(bool isLine)
    {

        char *string = new char[SIZE]();
        if (isLine)
        {
            cout << "Введите строку: ";
            cin.getline(string, SIZE);
            cin.ignore(INT16_MAX, '\n');
        }
        else
        {
            cout << "Введите слово/строку без пробелов";
            cin >> string;
            cin.ignore(INT16_MAX, '\n');
        }

        return string;
    }

    char getSymbolUser(const char *text)
    {
        char symbol;

        cout << "Введите символ (или \\ для пробела)" << text << ":";
        cin >> symbol;
        if (symbol == '\\')
            symbol = ' ';

        cin.ignore(INT16_MAX, '\n');

        return symbol;
    }

    int countWords(char *string)
    {
        std::locale ru("ru_RU.UTF8");
        int count = 0;
        int ln = strlen(string);

        for (int i = 0; i < ln - 1; i++)
        {
            bool normalMatch = (string[i] == ' ' && std::isalpha(string[i + 1], ru));
            bool firstWord = (std::isalpha(string[i], ru) && string[i + 1] == ' ' && count == 0);
            if (normalMatch || firstWord)
                ++count;
        }

        return count;
    }

    int *indexSymbols(char *string, char symbol, int &count)
    {
        int newLen = 0;
        int length = strlen(string);
        for (int iCh = 0; iCh < length; iCh++)
        {
            if (string[iCh] == symbol)
                newLen++;
        }
        count = newLen;
        int *indexes = nullptr;

        if (newLen > 0)
        {
            indexes = new int[newLen];

            int iIndexes = 0;
            for (int iCh = 0; iCh < length; iCh++)
            {
                if (string[iCh] == symbol)
                {
                    indexes[iIndexes] = iCh;
                    iIndexes++;
                }
            }
        }

        return indexes;
    }

    void changeCase(char *string)
    {
        uint8_t choice = static_cast<uint8_t>(choiceCase());
        uint16_t ln = strlen(string);
        doChangeCase(string,choice,ln);
    }

    void replace(char *string, int *indexes, int lnIndexes, char symbol)
    {
        for (int i = 0; i < lnIndexes; i++)
        {
            int currentIndex = indexes[i];
            string[currentIndex] = symbol;
        }
    }

    void print(const char *string)
    {
        cout << string << "\n";
    }

    void doOffset(char *string, int offset)
    {
        int length = strlen(string);
        for (int i = length; i > 0; --i)
        {
            string[i + offset] = string[i];
            string[i] = 0;
        }
    }

} // namespace cstr

namespace classStr
{
    using std::string;
    string getString(bool isLine)
    {
        string str;
        if (isLine)
        {
            char *c_string = new char[SIZE];
            cout << "Введите строку: ";
            cin.getline(c_string, SIZE);
            cin.ignore(INT16_MAX, '\n');
            str = {c_string};
            delete[] c_string;
        }
        else
        {
            cout << "Введите слово/строку без пробелов";
            cin >> str;
            cin.ignore(INT16_MAX, '\n');
        }
        return str;
    }

    uint16_t countWords(string str)
    {
        std::locale ru("ru_RU.UTF8");
        uint16_t ln = str.length();
        uint16_t count = 0;

        for (uint16_t i = 0; i < ln - 1; i++)
        {
            bool normalMatch = (str[i] == ' ' && std::isalpha(str[uint16_t(i + 1)], ru));
            bool firstWord = (std::isalpha(str[i], ru) && str[uint16_t(i + 1)] == ' ' && count == 0);

            if (normalMatch || firstWord)
                ++count;
        }

        return count;
    }

    uint8_t *indexSymbols(string str, char symbol, uint8_t &numberMatches)
    {
        uint8_t counter = 0;
        bool end = false;

        uint8_t position = 0;
        while (!end)
        {
            if (str.find(symbol, position) != str.npos)
            {
                ++counter;
                position = str.find(symbol, position) + 1;
            }
            else
                end = true;
        }

        uint8_t *index = nullptr;
        numberMatches = counter;

        position = 0;
        if (counter > 0)
        {
            index = new uint8_t[counter];
            for (uint8_t i = 0; i < counter; ++i)
            {
                if (str.find(symbol, position) != str.npos)
                {
                    index[i] = str.find(symbol, position);
                    position = index[i] + 1;
                }
            }
        }

        return index;
    }

    void changeCase(string &str)
    {
        uint8_t choice = static_cast<uint8_t>(choiceCase());
        doChangeCase(str,choice,uint16_t(str.length()+1));
    }

    void replace(string &str, uint8_t *indexes, uint8_t numberReplaces, char replace)
    {
        for (uint8_t i = 0; i < numberReplaces; i++)
        {
            str[indexes[i]] = replace;
        }
    }

    void print(string str)
    {
        cout << str;
        if (str.find('\n') == str.npos)
            cout << "\n";
    }

} // namespace classStr

int choiceCase()
{
    int choice;
    while (true)
    {
        cout << "Выберите способ изменения текста:\n"
                "1)Как в предложениях\n"
                "2)все строчные\n"
                "3)ВСЕ ПРОПИСНЫЕ\n"
                "4)Начинать С Прописных\n"
                "5)иЗМЕНИТЬ РЕГИСТР\n";
        cin >> choice;
        if (choice > 0 && choice < 6)
            return choice;
        else
            cout << "Incorrect values.Try again\n";
    }
}

