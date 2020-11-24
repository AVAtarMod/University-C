//9 лабораторная работа, все вспомогательные функции в functions.h

#include "functions.h"

int task1();
int task2();
int task3();
int task4();

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
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
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

    int arrayB[numberElements+1];
    arrayB[0] = numberElements;
    for (int i = 1; i <= numberElements; i++)
    {
        arrayB[i] = *(arrayA+i) * (*(arrayA+i)) + 2 * (*(arrayA+i)) - 1;
    }
    deleteArray(arrayA);
    printArray(arrayB,numberElements,"B");

    return 0;
}

int task2(){

    int *arrayA = generationAndPrintArray("A");
    short int numberElements = *arrayA;

    int arrayB[numberElements];
    arrayB[0] = numberElements;

    for (int i = 1; i <= numberElements; i++, arrayA++)
    {
        arrayB[i] = (*arrayA) * (*arrayA) + 2 * (*arrayA) - 1;
    }
    deleteArray(arrayA);
    printArray(arrayB,numberElements,"B");

    return 0;
}

int task3();
int task4();