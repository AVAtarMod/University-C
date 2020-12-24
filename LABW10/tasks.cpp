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

    generateFromUser(array, ln);
    print(array, ln);

    delete[] array;
}
void task2()
{
    const int ln = getLenghtUser();
    int *array = new int[ln];

    generateRandom(array, ln, -30, 30);
    print(array, ln);

    delete[] array;
}
void task3()
{
    const int ln = getLenghtRandom();
    int *array = new int[ln];

    generateRandom(array, ln, -30, 30);
    print(array, ln);

    int index = getIndexUser(ln, "Для вставки элемента");
    int element = getElementUser("Для вставки его в массив");

    pasteElement(&array, ln, index, element);
    print(array, ln + 1);

    delete[] array;
}
void task4()
{
    const int ln = getLenghtUser();
    int *array = new int[ln];

    generateFromUser(array, ln);

    int indexSearchedElement = indexElement(array, ln, getElementUser("Для получения индекса"));

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
    generateRandom(array, ln, -30, 30);
    print(array, ln);

    int maxElement = array[indexMinMaxElement(array, ln, isMax)];
    printf("\nМаксимальный элемент = %d\n", maxElement);

    int minElement = array[indexMinMaxElement(array, ln, isMin)];
    printf("\nМинимальный элемент  = %d\n", minElement);

    delete[] array;
}
void task6()
{
    const int ln = getLenghtRandom(5, 12);

    int *array = new int[ln];
    generateRandom(array, ln, -30, 30);
    print(array, ln);

    int indexMax = indexMinMaxElementWithConditions(array, ln, isMax, isOdd);
    int maxElement = array[indexMax];
    printf("\nМаксимальный нечетный элемент = %d\n", maxElement);

    int indexMin = indexMinMaxElementWithConditions(array, ln, isMin, isEven);
    int minElement = array[indexMin];

    printf("\nМинимальный четный элемент  = %d\n", minElement);
    delete[] array;
}
void task7()
{
    const int ln = getLenghtUser();
    int *array = new int[ln];

    generateFromUser(array, ln);
    int *arrayResult = searchIndexElements(array, ln, getElementUser("Для поиска количества вхождений"));

    if (arrayResult == nullptr)
        printf("Вхождений не найдено\n");
    else
        print(arrayResult, *arrayResult, "вхождений элементов", 1);

    delete[] array;
    delete[] arrayResult;
}
void task8()
{
    const int ln = getLenghtRandom(5, 12);
    int *array = new int[ln];
    generateRandom(array, ln, -30, 30);
    print(array, ln);

    int *arrayResult = elementsRelevantConditions(array, ln, isOdd);
    print(arrayResult, arrayResult[0], "элементов из нечетных чисел", 1);

    delete[] array;
    delete[] arrayResult;

}
void task9()
{

    const int ln = getLenghtUser();
    int *array = new int[ln];

    generateFromUser(array, ln);
    deleteElement(&array, ln, getIndexUser(ln, "Для удаления элемента"),1);

    print(array, ln - 1, "без удаленного элемента");

    delete[] array;
}
void task10()
{
}
void task11()
{
    const int ln = getLenghtUser();
    int *array = new int[ln];

    generateFromUser(array, ln);
    deleteElements(&array, ln, getElementUser("Для удаления элементов, равных введенному"),0);

    print(array, *array, "с удаленными элементами", 1);

    delete[] array;
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
