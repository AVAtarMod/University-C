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
    const int ln = getLenghtUser();
    int *array = new int[ln];

    array = generateRandom(array, ln, -30, 30);
    print(array, ln);

    delete[] array;
}
void task3()
{
    const int ln = getLenghtRandom();
    int *array = new int[ln];

    array = generateRandom(array, ln, -30, 30);
    print(array, ln);

    int index = getIndexUser(ln, "Для вставки элемента");
    int element = getElementUser("Для вставки его в массив");

    int *arrayB = pasteElement(array, ln, index, element);
    print(arrayB, ln + 1);

    delete[] array;
    delete[] arrayB;
}
void task4()
{
    const int ln = getLenghtUser();
    int *array = new int[ln];

    array = generateFromUser(array, ln);

    int indexSearchedElement = searchElement(array, ln, getElementUser("Для получения индекса"));

    if (indexSearchedElement == -1)
    {
        printf("\nЭлемент не найден\n");
    }
    else
        printf("\nИндекс элемента = %d\n", indexSearchedElement);

    delete[] array;
}
void task5()
{
    const int ln = getLenghtRandom(5, 12);

    int *array = new int[ln];
    array = generateRandom(array, ln, -30, 30);
    print(array, ln);

    int maxElement = searchMinMaxElement(array, ln, isMax);
    printf("\nИндекс максимального элемента = %d\n", maxElement);

    int minElement = searchMinMaxElement(array, ln, isMin);
    printf("\nИндекс минимального элемента  = %d\n", minElement);

    delete[] array;
}
void task6()
{
    const int ln = getLenghtRandom(5, 12);

    int *array = new int[ln];
    array = generateRandom(array, ln, -30, 30);
    print(array, ln);

    int indexMaxElement = searchMinMaxElementWithConditions(array, ln, isMax, isOdd);
    printf("\nИндекс максимального нечетного элемента = %d\n", indexMaxElement);

    int indexMinElement = searchMinMaxElementWithConditions(array, ln, isMin, isEven);
    printf("\nИндекс минимального четного элемента  = %d\n", indexMinElement);

    delete[] array;
}
void task7()
{
    const int ln = getLenghtUser();
    int *array = new int[ln];

    array = generateFromUser(array, ln);
    int *arrayResult = searchIndexElements(array, ln, getElementUser("Для поиска количества вхождений"));

    if (arrayResult)
        print(arrayResult, *arrayResult, "вхождений элементов", 1);
    else
        printf("Вхождений не найдено");

    delete[] array;
    delete[] arrayResult;
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
