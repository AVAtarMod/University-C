// Дано натуральное число. Написать логическую функцию проверяющую, является ли заданное число простым. Найти все простые числа близнецы, меньшие 1000

#include <iostream>
//Проверяет, простое число или нет
bool isSimple(int number);

int main()
{
    printf("\n\nПодходящие пары числел: \n");
    int counter = 0;

    for (int numberTwin1 = 1; numberTwin1 <= 1000; numberTwin1++)
    {
        int numberTwin2 = numberTwin1 + 2;
        if (isSimple(numberTwin1) && isSimple(numberTwin2))
        {
            printf("(%d %d)", numberTwin1, numberTwin2);
            counter++;
            if (counter % 3 == 0)
                printf(" \n");
        }
    }

    std::cout << "\n******\nБыло выведено " << counter << " пар чисел.\n\n";
    return 0;
}

bool isSimple(int number)
{
    bool isSimple;

    for (int divider = 1, counter = 0; divider <= number; divider++)
    {
        if (number % divider == 0)
            counter++;
        isSimple = (counter == 2) ? true : false;
    }

    return isSimple;
}
