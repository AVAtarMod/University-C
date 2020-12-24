#include <iostream>

#include "string.h"

void task1();
void task2();
void task3();
void task4();
void task7();

int main(int argc, char const *argv[])
{
    bool noData = false;
    if (argc == 1)
    {
        printf("###Вариант 3 ###\nВведите программу для запуска: ");
        argc++;
        noData = true;
    }
    for (int i = 1; i < argc; i++)
    {
        int choice;
        if (noData)
        {
            scanf("%d", &choice);
            std::cin.ignore(32767, '\n');
        }
        else
        {
            choice = std::stoi(argv[i]);
        }

        switch (choice)
        {
        case 1:
            printf("Задание №1\n");
            task1();
            break;
        case 2:
            printf("Задание №2\n");
            task2();
            break;
        case 3:
            printf("Задание №3\n");
            task3();
            break;
        case 4:
            printf("Задание №4\n");
            task4();
            break;
        case 7:
            printf("Задание №7\n");
            task7();
            break;

        default:
            printf("Номер задачи введен не верно либо не удалось конвертировать введенные данные\n");
            break;
        }
    }
}

void task1()
{
    char *line = cstr::getString(true);
    
    delete[] line;
}
void task2()
{
}
void task3()
{
}
void task4()
{
}
void task7()
{
}