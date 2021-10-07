#include <iostream>

#include "arrays2d.h"
#include "arrays1d.h"
#include "useful.h"

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task8();
void task9();
void task10();
void task12();
void task13();

int main(int argc, char const *argv[])
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
        case 5:
            printf("Задание №5\n");
            task5();
            break;
        case 6:
            printf("Задание №6\n");
            task6();
            break;
        case 8:
            printf("Задание №8\n");
            task8();
            break;
        case 9:
            printf("Задание №9\n");
            task9();
            break;
        case 12:
            printf("Задание №12\n");
            task12();
            break;
        case 13:
            printf("Задание №13\n");
            task13();
            break;

        default:
            printf("Номер задачи введен не верно либо не удалось конвертировать введенные данные\n");
            break;
        }
    }
}

void task1()
{
    int rows = 10, collumns = 10;
    int **array = array2d::init(rows, collumns);

    int sum = 0;
    for (int r = 0; r < rows; r++)
    {
        sum = r - 1;
        for (int c = 0; c < collumns; c++)
        {
            sum = (sum < 9) ? sum + 1 : 0;
            array[r][c] = sum;
        }
    }

    array2d::print(array, collumns, rows, "для №1 задания", 9);

    array2d::delete_(array, rows);
}
void task2()
{
    int *range = array2d::getRangeUser();
    int *size = array2d::getSizeUser();
    int **array = array2d::init(size[0], size[1]);
    array2d::fillRandom(array, range[0],range[1], size[0], size[1]);
    array2d::print(array, size[0], size[1], "", range[1]);

    int element = printAndScan<int>("Введите элемент чтобы найти количество его вхождений: ");

    int numOfOccurences = 0;
    for (int row = 0; row < size[0]; row++)
    {
        for (int col = 0; col < size[1]; col++)
        {
            if (array[row][col] == element)
            {
                numOfOccurences++;
            }
        }
    }

    if (numOfOccurences > 0)
        printf("\nЭлемент встречается %d раз(а)\n", numOfOccurences);
    else
        printf("\nВхождений не найдено.\n");

    array2d::delete_(array, size[0]);
    delete[] size;
    delete[] range;
}
void task3()
{
    int *range = array2d::getRangeRandom(-100, 100);
    int *size = array2d::getSizeUser();

    int **array = array2d::init(size[0], size[1]);
    array2d::fillRandom(array, range[0],range[1], size[0], size[1]);

    int *arrayFromMaxNumOfRow = new int[size[0]];
    for (int row = 0; row < size[0]; row++)
    {
        arrayFromMaxNumOfRow[row] = array[row][arrays1d::searchIndexMinMaxElement(array[row], size[1], arrays1d::isMax)];
    }
    arrays1d::print(arrayFromMaxNumOfRow, size[0], "из наибольших элементов");

    array2d::checkWork(array, size, range);

    array2d::delete_(array, size[0]);
    delete[] size;
    delete[] range;
    delete[] arrayFromMaxNumOfRow;
}
void task4()
{
    int *range = array2d::getRangeRandom(-100, 100);
    int *size = array2d::getSizeUser();

    int **array = array2d::init(size[0], size[1]);
    array2d::fillRandom(array, range[0],range[1], size[0], size[1]);

    int minimalSum = INT32_MAX; //modules elements of row
    int numberColl;

    int *collumn = new int[size[0]];
    for (int i = 0; i < size[1]; i++)
    {

        array2d::getCollumn(array, size[0], collumn, i);

        int currentSum = arrays1d::computeSumElements(collumn, size[0], arrays1d::alwaysTrue, arrays1d::doAbs);

        if (currentSum < minimalSum)
        {
            minimalSum = currentSum;
            numberColl = i;
        }
    }
    array2d::printCollumn(array, size[0], numberColl, "с минимальной суммой модулей");
    array2d::checkWork(array, size, range);
    array2d::delete_(array, size[0]);
    delete[] size;
    delete[] range;
    delete[] collumn;
}
void task5()
{
    int *size = array2d::getSizeUser();

    int **array = array2d::init(size[0], size[1]);
    array2d::fillRandom(array, -10, 10, size[0], size[1]);

    array2d::print(array, size[0], size[1], "(Исходный)", 10);
    for (int row = 0; row < size[0]; row++)
    {
        int start = array[row][0];
        for (int col = 0; col < size[1]; col++)
        {
            if (array[row][col] > 0)
            {
                array[row][col] *= start;
            }
            else if (array[row][col] < 0)
            {
                array[row][col] *= array[(size[0] - 1)][col];
            }
        }
    }
    array2d::print(array, size[0], size[1], "(После изменения)", 10);

    array2d::delete_(array, size[0]);
    delete[] size;
}
void task6()
{
    int *range = array2d::getRangeRandom(-100, 100);
    int *size = array2d::getSizeUser();

    int **array = array2d::init(size[0], size[1]);
    array2d::fillRandom(array, range[0],range[1], size[0], size[1]);

    int indexSortRow = array2d::searchSortRows(array, size[0], size[1], arrays1d::isMax);
    if (indexSortRow == -1)
        printf("Искомой строки нет");
    else
    {
        printf("Искомая строка имеет индекс = %d", indexSortRow);
    }

    array2d::delete_(array, size[0]);
    delete[] size;
    delete[] range;
}

void task8()
{
    int *range = array2d::getRangeRandom(-50, 50);
    int *size = array2d::getSizeUser();

    int **array = array2d::init(size[0], size[1]);
    array2d::fillUser(array, size[0], size[1], "#1");
    int **arrayB = array2d::init(size[0], size[1]);
    array2d::fillUser(arrayB, size[0], size[1], "#2");

    int *compared = array2d::compare(array, arrayB, size[0], size[1], array2d::isEqualElements);

    if (compared == nullptr)
    {
        printf("Совпадений не найдено\n");
    }
    else
    {
        arrays1d::print(compared, compared[0], "с одинаковыми элементами", 1);
    }

    array2d::delete_(array, size[0]);
    array2d::delete_(arrayB, size[0]);
    delete[] range;
    delete[] size;
}

void task9()
{
    int *range = array2d::getRangeRandom(-100, 100);
    int *size = array2d::getSizeUser();

    int **array = array2d::init(size[0], size[1]);
    array2d::fillRandom(array, range[0],range[1], size[0], size[1]);
    array2d::print(array, size[0], size[1], "", range[1]);

    array2d::invertRows(&array, size[0], true);
    array2d::print(array, size[0], size[1], "(строки инвертированы через указатели) ", range[1]);
    array2d::invertRows(&array, size[0], false, size[1]);
    array2d::print(array, size[0], size[1], "(строки инвертированы поэлементно) ", range[1]);

    array2d::delete_(array, size[0]);
    delete[] range;
    delete[] size;
}

void task12()
{
    int *range = array2d::getRangeRandom(-100, 100);
    int *size = array2d::getSizeUser();

    int **array = array2d::init(size[0], size[1]);
    array2d::fillRandom(array, range[0],range[1], size[0], size[1]);
    array2d::print(array, size[0], size[1], "исходный", range[1]);

    bool correctValue = false;
    while (!correctValue)
    {
        int index = printAndScan<int>("Введите номер строки, чтобы ее удалить: ");
        if (index < size[0] && index >= 0)
        {
            correctValue = true;
            delete[] array[index];
            array[index] = nullptr;
            array2d::rebalance(&array, size[0], size[1], size[0]);
        }
        else
        {
            printf("Допустимые значения : [%d;%d]", 0, size[0]);
        }
    }

    array2d::print(array, size[0] - 1, size[1], "без удаленных строк", range[1]);

    array2d::delete_(array, size[0] - 1);
    delete[] size;
    delete[] range;
}

void task13()
{
    int *range = array2d::getRangeRandom(-100, 100);
    int *size = array2d::getSizeUser();

    int **array = array2d::init(size[0], size[1]);
    array2d::fillRandom(array, range[0],range[1], size[0], size[1]);
    array2d::print(array, size[0], size[1], "", range[1]);

    int element = printAndScan<int>("Введите элемент, который требуется найти:");

    for (int row = 0; row < size[0]; row++)
    {
        if (arrays1d::searchElement(array[row], size[1], element) != -1)
        {
            delete[] array[row];
            array[row] = nullptr;
        }
    }
    array2d::rebalance(&array, size[0], size[1], size[0]);
    if (array == nullptr)
    {
        printf("Были удалены все строки, массив пуст\n");
    }
    else
    {
        array2d::print(array, size[0], size[1], "без строк с искомыми элементами", range[1]);
        array2d::delete_(array, size[0]);
    }

    delete[] size;
    delete[] range;
}

void task10()
{
}
