// Дано натуральное число. Написать функцию вычисления   суммы    цифр в числе. Используя  функцию  решить  задачу:  с  клавиатуры  считывается последовательность из Nцелых чисел. Вывести числа, сумма цифр которых больше 5

#include <iostream>

int sumDigits(int num);

int main()
{
    printf("\n\nВведите последовательность чисел, или -1 для остановки ввода: ");
    long int number;
    while (number != -1) {
        scanf("%ld", &number);
        if (sumDigits(abs(number)) > 5)
            printf("*%ld ", number);
        if (number == -1)
            printf("\nЗавершено считывание и обработка чисел.");
    }

    std::cout << "\n";

    return 0;
}

int sumDigits(int num)
{
    int result = 0;

    for (; num > 0; num /= 10) {
        result += num % 10;
    }

    return result;
}