// Найти все двузначные числа, в которых есть цифра N или само число делится на N
#include <iostream>
int main()
{
    int n, counter = 0;
    printf("\n\nВведите число: ");
    scanf("%d", &n);

    for (int num = 10; num != 100; num++)
        if (num % n == 0 || (num - (num - num % 10)) == n || (num - num % 10) / 10 == n) {
            printf("\nЧисло, соответствующее условиям = %d", num);
            counter++;
        }
    printf("\n\n -- Общее количество чисел = %d --\n", counter);
    return 0;
}