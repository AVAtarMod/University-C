// Дано    натуральное число,  представленное  в десятичной  системе  счисления. Написать функцию, вычисляющую количество ненулевых разрядов, стоящих на чётных  местах  в двоичной  записи этого числа  (разряды  нумеруются  с  0 с младшего разряда).

#include <iostream>
int number_NotZeroEvenDigitsInBinaryNumber(int number);

int main()
{

    printf("Введите число: ");
    int number;
    printf("Результат выполнения = %d\n", number_NotZeroEvenDigitsInBinaryNumber(scanf("%d", &number)));

    return 0;
}

int number_NotZeroEvenDigitsInBinaryNumber(int number)
{
    int number_NotZeroEvenDigitsInBinaryNumber = 0;

    for (; number > 0; number = number >> 2)
        if (number & 0x1 == 1)
            number_NotZeroEvenDigitsInBinaryNumber++;

    return number_NotZeroEvenDigitsInBinaryNumber;
}