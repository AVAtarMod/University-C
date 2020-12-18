#include <iostream>
#include <random>
#include <chrono>

#include "arrays2d.h"

namespace array2d
{
    int *getRangeUser()
    {
        int *choice = new int[2];

        std::printf("Введите числа А и В диапазона значений псевдо-случайных чисел [А;В] : ");
        std::scanf("%d %d", &choice[0], &choice[1]);
        std::cin.ignore(32767, '\n');
        if (choice[0] > choice[1])
        {
            int temp = choice[0];
            choice[0] = choice[1];
            choice[1] = temp;
        }

        return choice;
    }

    int *getSizeUser()
    {
        int *size = new int[2];

        for (bool isDataRight = false; !isDataRight;)
        {
            printf("Введите размер массива (2 числа): ");
            scanf("%d %d", &size[0], &size[1]);
            std::cin.ignore(32767, '\n');
            if (size[0] < 0 || size[1] < 0)
            {
                printf("Введены некорректные значения. Попробуйте снова\n");
                isDataRight = false;
            }
            else
                isDataRight = true;
        }

        return size;
    }

    int *getRangeRandom(int A, int B)
    {
        int *range = new int[2]();

        range[0] = getRandomNumber(A,B);
        range[1] = range[0] * -1;

        return range;
    }

    int **init(const int rows, const int collumns)
    {
        int **array = new int *[rows];
        for (int i = 0; i < rows; i++)
        {
            array[i] = new int[collumns]();
        }

        return array;
    }

    int **fillRandom(int **array, int leftLim, int rightLim, const int rows, const int collumns)
    {
        std::mt19937 engine(static_cast<unsigned long>(clock()));
        std::uniform_int_distribution<int> random(leftLim, rightLim);

        for (int row = 0; row < rows; row++)
        {
            for (int coll = 0; coll < collumns; coll++)
            {
                array[row][coll] = random(engine);
            }
        }

        return array;
    }

    int isSortRow(int **array, int rows, int collumns, bool condition(int, int))
    {
        int indexRow = -1;
        for (int row = 0; row < rows; row++)
        {
            bool isSortRow = true;
            for (int col = 1; isSortRow && col < collumns; col++)
            {
                if (condition(array[row][(col - 1)], array[row][col]) == false)
                {
                    isSortRow = false;
                }
            }
            if (isSortRow)
                indexRow = row;
        }
        return indexRow;
    }

    void print(int **array, int rows, int collumns, const char *text, int maxElement)
    {
        maxElement = numDigits(maxElement);
        printf("\nМассив %d x %d %s :\n", collumns, rows, text);

        for (int row = 0,printRow = row; row < rows; row++)
        {
            if (array[row])
            {
                printf("%d [ ", printRow);
                for (int coll = 0; coll < collumns; coll++)
                {
                    printf("%*d,", (maxElement + 1), array[row][coll]);
                }
                printf("\b ]\n");
                ++printRow;
            }
        }
    }

    void checkWork(int **array, int *size, int *range)
    {
        printf("Вывести исходный массив для проверки?[1 = да][0 = нет]: ");
        int choice;

        for (bool correctExit = false; !correctExit;)
        {
            scanf("%d", &choice);
            std::cin.ignore(32767, '\n');
            if (choice == 1)
            {
                array2d::print(array, size[0], size[1], "", range[1]);
                correctExit = true;
            }
            else if (choice != 0)
            {
                printf("Значение не верно, попробуйте снова.\n");
            }
            else
            {
                correctExit = true;
            }
            
        }
    }

    int **copy(int **array, int rows, int collumns)
    {
        int **newArray = new int *[rows];
        for (int row = 0; row < rows; row++)
        {
            newArray[row] = new int[collumns]();
        }

        for (int row = 0; row < rows; row++)
        {
            if (array[row])
                for (int col = 0; col < collumns; col++)
                {
                    newArray[row][col] = array[row][col];
                }
            else
            {
                --rows;
                --row;
            }
        }
        return newArray;
    }

    void delete_(int **array, int rows)
    {
        for (int row = 0; row < rows; row++)
        {
            delete[] array[row];
        }
        delete[] array;
    }

} // namespace array2d

int getRandomNumber(int leftLim, int rightLim)
{
    unsigned int now = static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count() % 100000);
    std::default_random_engine engine(now);
    std::uniform_int_distribution<int> random(leftLim, rightLim);

    return random(engine);
}

int numDigits(int number)
{
    number = abs(number);
    int result = 0;
    for (int digit = 1; number % digit != number; digit *= 10)
    {
        result++;
    }
    return result;
}
