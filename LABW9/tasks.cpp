//9 лабораторная работа, все вспомогательные функции в functions.h
//В данной лабораторной работе массив увеличен на 1 индекс, так как размер массива хранится в 1 элементе.

//OPT: доделать старт

#include <iostream>
#include <random>
using std::cout;
using std::endl;

#include "functions.h"

int main()
{
    printf("\n\nВведите номер задачи для ее запуска: ");
    int choose;
    scanf("%d", &choose);
    switch (choose)
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
    default:
        printf("Задачи под данным номером не существует или она не решена");
        break;
    }
}

int task1()
{
    int *arrayA = generationAndPrintArray("A", 1);
    short int numberElements = *arrayA;

    int *arrayB = new int[numberElements]();
    *arrayB = numberElements;
    for (int i = 1; i <= numberElements; i++)
    {
        arrayB[i] = *(arrayA + i) * (*(arrayA + i)) + 2 * (*(arrayA + i)) - 1;
    }
    deleteArray(arrayA);
    printArray(arrayB, numberElements, "B");
    deleteArray(arrayB);

    return 0;
}

int task2()
{

    int *arrayA = generationAndPrintArray("A", 1);
    short int numberElements = *arrayA;

    bool *arrayB = new bool[numberElements]();
    *arrayB = numberElements;
    for (int i = 1; i <= numberElements; i++)
    {
        arrayB[i] = (abs(arrayA[i]) % 3 == 0) ? true : false;
    }
    deleteArray(arrayA);

    printArray(arrayB, numberElements, "B", 1);
    deleteArray(arrayB);

    return 0;
}

int task3()
{
    int *arrayA = generationAndPrintArray("A", 1);
    short int numberElements = *arrayA;

    int *arrayB = new int[numberElements]();
    *arrayB = numberElements;
    for (int i = 1; i <= numberElements; i++)
    {
        int result = 0;
        for (int c = 1, *p = (arrayA + c); c <= i; c++, p++)
        {
            result += *p;
        }
        arrayB[i] = result;
    }
    deleteArray(arrayA);

    printArray(arrayB, numberElements, "B", 1);
    deleteArray(arrayB);

    return 0;
}

int task4()
{
    int *arrayA = generationAndPrintArray("A", 1);
    short int numberElements = *arrayA;

    int *arrayB = elementsRelevantConditions(arrayA, numberElements, isSimple, 1);
    if (arrayB == nullptr)
    {
        printArray(arrayB, numberElements, "из простых чисел", 1, false);
        deleteArray(arrayB);
    }
    deleteArray(arrayA);
    return 0;
}

int task5()
{
    int *multiplicationTable = new int[100];

    cout << "Таблица умножения:"
         << "\n     ";
    for (int i = 1; i <= 10; i++)
    {
        cout << i << "  ";
    }
    cout << "\n";

    int *p = multiplicationTable;
    for (int a = 1; a <= 10; a++)
    {
        if (a < 10)
            cout << a << " [ ";
        else
            cout << a << "[ ";

        for (int b = 1; b <= 10; b++, p++)
        {
            *p = a * b;
            if (*p < 10)
                cout << " ";
            cout << *p;
            if (*p < 100)
                cout << " ";
        }
        cout << " ]\n";
    }
    cout << "\n"
         << endl;
    deleteArray(multiplicationTable);

    return 0;
}

int task6()
{
    int *arrayA = generationAndPrintArray("A", 1);
    short int numberElements = *arrayA;

    int *arrayB = indexesRelevantConditions(arrayA, numberElements, isNegative, 1);

    deleteArray(arrayA);

    if (arrayB == nullptr)
    {
        cout << "*Отрицательных чисел не найдено\n"
             << endl;
    }
    else
        printArray(arrayB, numberElements, "из номеров отрицательных элементов", 1, false);

    deleteArray(arrayB);
    return 0;
}

int task7()
{
    int *arrayA = generationAndPrintArray("A", 1);
    short int numberElements = *arrayA;

    int index = indexRelevantConditions(arrayA, numberElements, isDivideBy7, 1);
    deleteArray(arrayA);

    if (index == -1)
        cout << "*Чисел, кратных 7 не найдено\n"
             << endl;
    else
        printf("Индекс числа кратного 7 = %d\n\n", index);
    return 0;
}

int task8()
{
    int *arrayA = generationAndPrintArray("A", 1);
    short int numberElements = *arrayA;

    for (int i = 2; i < numberElements; i++)
    {
        if ((i - 1) % 2 == 0)
        {
            *(arrayA + i) = *(arrayA + i) * *(arrayA + i);
        }
        else
        {
            *(arrayA + i) = 2 * *(arrayA + i);
        }
    }
    printArray(arrayA, numberElements, "A", 1, true);
    deleteArray(arrayA);
    return 0;
}

int task9()
{
    int *arrayA = generationAndPrintArray("A", 1);
    short int numberElements = *arrayA;

    for (int *P = (arrayA + 2), i = 2; i < numberElements; P++, i++)
    {
        int element = *(arrayA + i);
        if ((i - 1) % 2 == 0 && *(arrayA + i) < 0)
        {
            *(arrayA + i) = element + i - 1;
        }
    }
    printArray(arrayA, numberElements, "A", 1, true);
    deleteArray(arrayA);
    return 0;
}

int task10()
{
    int *arrayM = generationAndPrintArray("M", 1);
    short int numberElements = *arrayM;

    int *range = new int[2]();
    getRangeUser(numberElements - 1, range);
    //OPT исправить ошибки
    range[0]++;
    range[1]++;

    int result = productElements(arrayM, range[1] + 1, range[0]);
    cout << "Результат: " << result << "\n";

    deleteArray(arrayM);
    deleteArray(range);
    return 0;
}
int task11()
{
    int *arrayA = generationAndPrintArray("A", 1);
    short int numberElements = *arrayA;

    int start = indexRelevantConditions(arrayA, numberElements + 1, isEndsIn3, 1);
    if (start == -1)
    {
        cout << "Отрезок, соответствующий условиям не найден \n";
    }
    else
    {
        int product = productElements(arrayA,numberElements+1,start+2);
        cout << "Результат: " << product << "\n\n";
    }
    deleteArray(arrayA);
    return 0;
}