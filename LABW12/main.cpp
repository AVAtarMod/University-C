#include <iostream>

#include "string.h"
#include "useful.h"

using std::cin;
using std::cout;

void task1cstr();
void task2cstr();
void task3cstr();
void task4cstr();
void task7cstr();

void task1();
void task2();
void task3();
void task4();
void task7();

int choiceImplementation();

int main(int argc, char const *argv[])
{
    bool noData = false;
    if (argc == 1)
    {
        printf("### Вариант 3 ###");
        printf("\nВведите программу для запуска: ");
        argc++;
        noData = true;
    }
    for (int i = 1; i < argc; i++)
    {
        int choice;
        if (noData)
        {
            scanf("%d", &choice);
        }
        else
        {
            choice = std::stoi(argv[i]);
        }

        switch (choice)
        {
        case 1:
            printf("Задание №1\n");
            if (choiceImplementation() == 1)
                task1cstr();
            else
                task1();
            break;
        case 2:
            printf("Задание №2\n");
            if (choiceImplementation() == 1)
                task2cstr();
            else
                task2();
            break;
        case 3:
            printf("Задание №3\n");
            if (choiceImplementation() == 1)
                task3cstr();
            else
                task3();
            break;
        case 4:
            printf("Задание №4\n");
            if (choiceImplementation() == 1)
                task4cstr();
            else
                task4();
            break;
        case 7:
            printf("Задание №7\n");
            if (choiceImplementation() == 1)
                task7cstr();
            else
                task7();
            break;

        default:
            printf("Номер задачи введен не верно либо не удалось конвертировать введенные данные\n");
            break;
        }
    }
}

int choiceImplementation()
{
    while (true)
    {
        int choice = printAndScan<int>("Выберите реализацию: c-string[1] или std::string[2]: ");
        if (choice == 1 || choice == 2)
        {
            std::cin.ignore(32767, '\n');
            return choice;
        }
        else
            cout << "Введеные данные неверны.\n";
    }
}

void task1cstr()
{
    char *line = cstr::getStringUser(true);
    char symbol = cstr::getSymbolUser(" для замены на другой символ");
    int numberReplaces;
    int *indexes = cstr::indexSymbols(line, symbol, numberReplaces);

    char replace = cstr::getSymbolUser(", на который нужно заменить");
    cstr::replace(line, indexes, numberReplaces, replace);
    cstr::print(line);

    delete[] line;
    delete[] indexes;
}
void task1()
{
    std::string str = classStr::getString(true);
    uint8_t replaces;
    uint8_t *indexes = classStr::indexSymbols(str, cstr::getSymbolUser(" для замены на другой символ"), replaces);
    classStr::replace(str, indexes, replaces, cstr::getSymbolUser(", на который нужно заменить"));

    classStr::print(str);
    delete[] indexes;
}
void task2cstr()
{
    char *telegram = cstr::getStringUser(true);
    uint16_t words = cstr::countWords(telegram);
    uint16_t cost = printAndScan<int>("Введите стоимость телеграммы: ");
    cout << "Стоимость телеграммы: " << words * cost << "\n";

    delete[] telegram;
}
void task2()
{
    std::string str = classStr::getString(true);
    uint16_t words = classStr::countWords(str);
    uint16_t cost = printAndScan<int>("Введите стоимость телеграммы: ");
    cout << "Стоимость телеграммы: " << words * cost << "\n";
}
void task3cstr()
{
    char *line = cstr::getStringUser(true);
    cstr::changeCase(line);
    cstr::print(line);

    delete[] line;
}
void task3()
{
    std::string str = classStr::getString(true);
    classStr::changeCase(str);
    classStr::print(str);
}
void task4cstr()
{
}
void task4()
{
}
void task7cstr()
{
}
void task7()
{
}