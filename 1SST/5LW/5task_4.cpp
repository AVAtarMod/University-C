// Среди двузначных чисел найти те, сумма квадратов цифр которых делится на 13.

#include <iostream>

int main()
{
    int n = 10, count = 0;
    printf("\nЧисла, соответствующие условиям = ");

    for (; n < 100; n++) {
        int ten = n / 10;
        int one = n - (ten * 10);
        int sum = ten * ten + one * one;

        if (sum % 13 == 0) {
            printf("%d;", n);
            count++;
        }
    }
    printf("\n\n -- Общее количество чисел = %d --\n", count);

    return 0;
}