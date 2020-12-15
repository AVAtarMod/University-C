#include <iostream>
#include <random>

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

    int *getSizeUser(bool rowsEqualCollumns)
    {
        if (rowsEqualCollumns)
        {
            int *size = nullptr;
            printf("Введите размер массива (1 число): ");
            scanf("%d", size);
            std::cin.ignore(32767, '\n');
            return size;
        }
        else
        {
            int *size = new int[2];

            for (bool isDataRight = false; !isDataRight;)
            {
                printf("Введите размер массива (2 числа через пробел, сначала количество строк, затем столбцов): ");
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
    }

    int **init(const int rows, const int collumns)
    {
        int **array = new int *[rows];
        for (int i = 0; i < collumns; i++)
        {
            array[i] = new int[collumns];
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

    void print(int **array, const int collumns, const int rows, const char *text, int maxElement)
    {
        maxElement = numDigits(maxElement);
        printf("\nМассив %d x %d %s :\n", collumns, rows, text);

        if (maxElement == 0)
        {
            for (int row = 0; row < rows; row++)
            {
                printf("%d | ", row);
                for (int coll = 0; coll < collumns; coll++)
                {
                    printf("%d,", array[row][coll]);
                }
                printf("\b |\n");
            }
        }
        else
        {
            for (int row = 0; row < rows; row++)
            {
                printf("%d | ", row);
                for (int coll = 0; coll < collumns; coll++)
                {
                    printf("%*d,", (maxElement + 1), array[row][coll]);
                }
                printf("\b |\n");
            }
        }
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

} // namespace array2d
