// Даны натуральные числа m, n. Получить все кратные им числа, меньшие m*n.

#include <iostream>

int main()
{

    int m, n, warn = 0;

    printf("\n\nВведите числа m и n через пробел: ");
    scanf("%d %d", &m, &n);

    printf("Числа,соответствующие условиям = ");

    int rn = (m > n) ? m : n;
    for (; rn < m * n; rn++) {
        if (rn % m == 0 && rn % n == 0 && rn < m * n) {
            printf("%d;", rn);
            warn++;
        }
    }

    if (warn == 0) {
        printf("...их нет");
    }
    printf("\n\n");

    return 0;
}