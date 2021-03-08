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
        std::cin.ignore(INT16_MAX, '\n');
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
            std::cin.ignore(INT16_MAX, '\n');
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

        range[0] = getRandomNumber(A, B);
        range[1] = getRandomNumber(A, B);

        if (range[0] > range[1])
        {
            int t = range[0];
            range[0] = range[1];
            range[1] = t;
        }

        return range;
    }

    int **init(const int rows, const int collumns)
    {
        if (rows == 0)
            return nullptr;
        else
        {
            int **array = new int *[rows];
            for (int i = 0; i < rows; i++)
            {
                array[i] = new int[collumns]();
            }
            return array;
        }
    }

    void fill(int **array, const int rows, const int collumns)
    {
        int i = 0;
        for (int row = 0; row < rows; row++)
        {
            for (int coll = 0; coll < collumns; coll++)
            {
                array[row][coll] = i++;
            }
        }
    }

    void fillUser(int **array, const int rows, const int collumns, const char *text)
    {
        printf("\n\nВведите значения массива %s\n", text);
        for (int row = 0; row < rows; row++)
        {
            printf("Строка %d/%d [%d числа(ел)]: ", row + 1, rows, collumns);
            for (int coll = 0; coll < collumns; coll++)
            {
                scanf("%d", &array[row][coll]);
            }
            std::cin.ignore(INT16_MAX, '\n');
        }
    }

    int searchSortRows(int **array, int rows, int collumns, bool condition(int, int))
    {
        int indexRow = -1;
        for (int row = 0; row < rows; row++)
        {
            bool isSortRow = true;
            for (int col = 1; isSortRow && col < collumns; col++)
            {
                if (!condition(array[row][(col - 1)], array[row][col]))
                {
                    isSortRow = false;
                }
            }
            if (isSortRow)
                indexRow = row;
        }
        return indexRow;
    }

    void getCollumn(int **array, int rows, int *result, int collumn)
    {
        for (int row = 0; row < rows; row++)
        {
            result[row] = array[row][collumn];
        }
    }

    void invertRows(int ***array, int rows, bool fast, int collumns)
    {
        const int lastRow = rows / 2;
        const int rowsIndex = rows - 1;
        if (fast)
        {
            for (int row = 0; row < lastRow; row++)
            {
                int *temp = (*array)[row];
                (*array)[row] = (*array)[rowsIndex - row];
                (*array)[rowsIndex - row] = temp;
            }
        }
        else
        {
            for (int row = 0; row < lastRow; row++)
            {
                for (int col = 0; col < collumns; col++)
                {
                    int tempElement = (*array)[row][col];
                    (*array)[row][col] = (*array)[rowsIndex - row][col];
                    (*array)[rowsIndex - row][col] = tempElement;
                }
            }
        }
    }

    int *compare(int **arrayA, int **arrayB, int rowsMin, int collumnsMin, bool comparator(int, int, int &))
    {
        int ln = 0;
        for (int row = 0; row < rowsMin; row++)
        {
            for (int col = 0; col < collumnsMin; col++)
            {
                int i;
                if (comparator(arrayA[row][col], arrayB[row][col], i))
                {
                    ln++;
                }
            }
        }

        int *arrayResult = new int[ln + 1];
        arrayResult[0] = ln + 1;
        int iterResult = 1;

        for (int row = 0; row < rowsMin; row++)
        {
            for (int col = 0; col < collumnsMin; col++)
            {
                if (comparator(arrayA[row][col], arrayB[row][col], arrayResult[iterResult]))
                {
                    iterResult++;
                }
            }
        }

        if (!ln)
        {
            delete[] arrayResult;
            return nullptr;
        }
        else
        {
            return arrayResult;
        }
    }

    void print(int **array, int rows, int collumns, const char *text, int maxElement)
    {
        maxElement = numDigits(maxElement);
        printf("\nМассив %d x %d %s :\n", collumns, rows, text);

        for (int row = 0, printRow = row; row < rows; row++)
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

    void printCollumn(int **array, const int rows, const int collumn, const char *text)
    {
        printf("Столбец %s: [ ", text);
        for (int row = 0; row < rows; row++)
        {
            printf("%d; ", array[row][collumn]);
        }
        printf("]\n");
    }

    void checkWork(int **array, int *size, int *range, const char *text)
    {
        printf("Вывести исходный массив %s для проверки?[1 = да][0 = нет]: ", text);
        int choice;

        int i = 0;
        scanf("%d", &choice);
        std::cin.ignore(INT16_MAX, '\n');
        if (choice == 1)
        {
            array2d::print(array, size[0], size[1], "", range[1]);
            i++;
        }
        else if (choice != 0)
        {
            printf("Значение не верно, попробуйте снова.\n");
        }
    }

    void copy(int **source, int rows, int collumns, int **destination)
    {
        for (int destRow = 0, srcRow = 0; srcRow < rows; srcRow++)
        {
            if (source[srcRow] != nullptr)
            {
                for (int col = 0; col < collumns; col++)
                {
                    destination[destRow][col] = source[srcRow][col];
                }
                destRow++;
            }
        }
    }

    void delete_(int **array, int rows)
    {
        for (int row = 0; row < rows; row++)
        {
            if (array[row] != nullptr)
            {
                delete[] array[row];
            }
        }
        delete[] array;
    }

    void rebalance(int ***array, int rows, int collumns, int &newCollumns)
    {
        //Add link rows
        int counter = 0;
        for (int row = 0; row < rows; row++)
        {
            if (array[0][row] == nullptr)
                counter++;
        }
        if (rows - counter <= 0)
        {
            delete_(array[0], rows);
            array[0] = nullptr;
            newCollumns = 0;
        }
        else
        {
            int **result = init(rows - counter, collumns);
            copy(array[0], rows, collumns, result);
            delete_(array[0], rows);
            array[0] = result;
            newCollumns = rows - counter;
        }
    }

    bool isEqualElements(int elFrom1Ar, int elFrom2Ar, int &result)
    {
        if (elFrom1Ar == elFrom2Ar)
        {
            result = elFrom2Ar;
            return true;
        }

        return false;
    }

} // namespace array2d

int getRandomNumber(int from, int to)
{
    try
    {
        if (from > to)
            throw "Incorrect couple 'from - to' for generating random numbers";
    }
    catch (const char *message)
    {
        std::cerr << message << '\n';
        exit(1);
    }

    unsigned int now = static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count() % 10000);
    std::mt19937 engine(now);
    std::uniform_int_distribution<int> random(from, to);

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
