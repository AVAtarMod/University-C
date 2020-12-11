//9 лабораторная работа, все вспомогательные функции в functions.h
//В данной лабораторной работе массив увеличен на 1 индекс, так как размер массива хранится в 1 элементе.

//TODO: доделать старт

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
    int *arrayA = generationAndPrintArray("A");
    short int numberElements = *arrayA;

    int *arrayB = new int[numberElements];
    *arrayB = numberElements;
    for (int i = 1; i <= numberElements; i++)
    {
        arrayB[i] = *(arrayA + i) * (*(arrayA + i)) + 2 * (*(arrayA + i)) - 1;
    }
    deleteArray(&arrayA);
    printArray(arrayB, numberElements,"B");
    deleteArray(&arrayB);

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
    deleteArray(&arrayA);

    printArray(arrayB, numberElements, "B");
    deleteArray(&arrayB);

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
    deleteArray(&arrayA);

    printArray(arrayB, numberElements, "B");
    deleteArray(&arrayB);

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
    deleteArray(&arrayA);

    if (!counter)
        cout << "*Простых чисел не найдено\n"
             << endl;
    else
        printArray(arrayB, numberElements, "из простых чисел", false);

    deleteArray(&arrayB);
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
    deleteArray(&multiplicationTable);

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
        if (*P < 0)
        {
            arrayB[i] = i;
            counter++;
        }
    }
    deleteArray(&arrayA);

    if (!counter)
        cout << "*Отрицательных чисел не найдено\n"
             << endl;
    else
        printArray(arrayB, numberElements, "из номеров отрицательных элементов", false);

    deleteArray(&arrayB);
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
        if (*P % 7 == 0)
        {
            arrayB[1] = i - 1;
            counter++;
        }
    }
    deleteArray(&arrayA);

    if (!counter)
        cout << "*Чисел, кратных 7 не найдено\n"
             << endl;
    else
        printArray(arrayB, 2, "индекса числа, кратных 7");

    deleteArray(&arrayB);
    return 0;
}

int task8()
{
    int *arrayA = generationAndPrintArray("A");
    short int numberElements = *arrayA;

    for (int *P = (arrayA + 2), i = 2; i < numberElements; P++, i++)
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
    printArray(arrayA, numberElements, "A", true);
    deleteArray(&arrayA);
    return 0;
}

int task9()
{
    int *arrayA = generationAndPrintArray("A");
    short int numberElements = *arrayA;

    for (int *P = (arrayA + 2), i = 2; i < numberElements; P++, i++)
    {
        int element = *(arrayA + i);
        if ((i - 1) % 2 == 0 && *(arrayA + i) < 0)
        {
            *(arrayA + i) = element + i - 1;
        }
    }
    printArray(arrayA, numberElements, "A", true);
    deleteArray(&arrayA);
    return 0;
}

int task10()
{
    int *arrayM = generationAndPrintArray("M");
    short int numberElements = *arrayM;

    int A, B;
    cout << "Введите границы А,Б : ";
    scanf("%d %d", &A, &B);
    A++;
    B++;
    if (A > B)
    {
        int temp = A;
        A = B;
        B = temp;
    }
    if (A <= numberElements && B <= numberElements && A >= 0 && B >= 0)
    {
        int result = 1;
        for (int *P = (arrayM + A), i = A; i <= B; P++, i++)
        {
            result *= *P;
        }
        cout << "Результат: " << result << "\n";
    }
    else
        cout << "Введены некорректные значения.";

    return 0;
}
int task11()
{
    int *arrayA = generationAndPrintArray("A");
    short int numberElements = *arrayA;

    bool numberIsExist = false;
    int *startAdress, startNumber;
    for (int i = 1, *p = arrayA; i < numberElements; i++, p++)
    {
        if (*p < 0 && abs(*p) % 10 == 3)
        {
            startAdress = (p+1);
            startNumber = (i+1);
            numberIsExist = true;
        }
    }
    if (numberIsExist)
    {
        long long int result = 1;
        for (int i = startNumber, *p = startAdress; i <= numberElements; i++, p++)
        {
            result *= *p;
        }
        cout << "Результат выполнения = " << result << "\n";
    }
    else
        cout << "Отрезок, соответствующий условиям не найден \n";
    return 0;
}