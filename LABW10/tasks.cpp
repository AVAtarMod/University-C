#include <iostream>

#include "array.h"
int main(int argc, char *argv[])
{
    bool noData = false;
    if (argc == 1)
    {
        printf("Введите программу для запуска: ");
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
            task1();
            break;
        case 2:
            task2();
            break;
        case 3:
            task3();
            break;
        case 4:
            task4();
            break;
        case 5:
            task5();
            break;
        case 6:
            task6();
            break;
        case 7:
            task7();
            break;
        case 8:
            task8();
            break;
        case 9:
            task9();
            break;
        case 10:
            task10();
            break;
        case 11:
            task11();
            break;
        case 12:
            task12();
            break;
        case 13:
            task13();
            break;
        case 14:
            task14();
            break;
        default:
            printf("Номер задачи введен не верно либо не удалось конвертировать введенные данные");
            break;
        }
    }
}

void task1()
{
    const int ln = getLenghtUser();
    int *array = new int[ln];

    array = generateFromUser(array, ln);
    print(array, ln);

    delete[] array;
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
void task5()
{
}
void task6()
{
}
void task7()
{
}
void task8()
{
}
void task9()
{
}
void task10()
{
}
void task11()
{
}
void task12()
{
}
void task13()
{
}
void task14()
{
}
