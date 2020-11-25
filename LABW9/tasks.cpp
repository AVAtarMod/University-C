//9 лабораторная работа, все вспомогательные функции в functions.h
//В данной лабораторной работе массив увеличен на 1 индекс, так как размер массива хранится в 1 элементе.

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
    default:
        printf("Задачи под данным номером не существует или она не решена");
        break;
    }
}

int task1()
{
    int *arrayA = generationAndPrintArray("A");
    short int numberElements = *arrayA;

    int *arrayB = new int[numberElements];
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

    int *arrayA = generationAndPrintArray("A");
    short int numberElements = *arrayA;

    bool *arrayB = new bool[numberElements];
    *arrayB = numberElements;
    for (int i = 1; i <= numberElements; i++)
    {
        arrayB[i] = (abs(arrayA[i]) % 3 == 0) ? true : false;
    }
    deleteArray(arrayA);

    printArray(arrayB, numberElements, "B");
    deleteArray(arrayB);

    return 0;
}

int task3()
{

    int *arrayA = generationAndPrintArray("A");
    short int numberElements = *arrayA;

    int *arrayB = new int[numberElements];
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

    printArray(arrayB, numberElements, "B");
    deleteArray(arrayB);

    return 0;
}

int task4()
{
    int *arrayA = generationAndPrintArray("A");
    short int numberElements = *arrayA;

    int *arrayB = new int[numberElements];
    *arrayB = numberElements;

    int counter = 0;
    for (int i = 1, *P = (arrayA + i); i <= numberElements; i++, P++)
    {
        int result = 0;
        int c = 0;
        for (int divisor = 2; divisor < *P; divisor++)
        {
            if (*P % divisor != 0)
            {
                c++;
            }
        }
        if (c == 0)
        {
            arrayB[i] = *P;
            counter++;
        }
    }
    deleteArray(arrayA);

    if (!counter)
        cout << "*Простых чисел не найдено\n"
             << endl;
    else
        printArray(arrayB, numberElements, "из простых чисел", false, false);

    deleteArray(arrayB);
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
    int *arrayA = generationAndPrintArray("A");
    short int numberElements = *arrayA;

    int *arrayB = new int[numberElements];
    *arrayB = numberElements;

    int counter = 0;
    for (int i = 1, *P = (arrayA + i); i <= numberElements; i++, P++)
    {
        int result = 0;
        if (*P < 0)
        {
            arrayB[i] = i;
            counter++;
        }
    }
    deleteArray(arrayA);

    if (!counter)
        cout << "*Отрицательных чисел не найдено\n"
             << endl;
    else
        printArray(arrayB, numberElements, "из номеров отрицательных элементов", false, false);

    deleteArray(arrayB);
    return 0;
}

int task7()
{
    int *arrayA = generationAndPrintArray("A");
    short int numberElements = *arrayA;

    int *arrayB = new int[2];
    *arrayB = numberElements;

    int counter = 0;
    for (int i = 1, *P = (arrayA + i); i < numberElements; P++, i++)
    {
        int result = 0;
        if (*P % 7 == 0)
        {
            arrayB[1] = i - 1;
            counter++;
        }
    }
    deleteArray(arrayA);

    if (!counter)
        cout << "*Чисел, кратных 7 не найдено\n"
             << endl;
    else
        printArray(arrayB, 2, "индекса числа, кратных 7");

    deleteArray(arrayB);
    return 0;
}

int task8()
{
    int *arrayA = generationAndPrintArray("A");
    short int numberElements = *arrayA;

    for (int *P = (arrayA + 2), i = 2; i < numberElements; P++, i++)
    {
        int result = 0;
        if ((i - 1) % 2 == 0)
        {
            *(arrayA + i) = *(arrayA + i) * *(arrayA + i);
        }
        else
        {
            *(arrayA + i) = 2 * *(arrayA + i);
        }
    }
    printArray(arrayA, numberElements, "A", true);
    deleteArray(arrayA);
    return 0;
}