// Пусть n – натуральное число и пусть n!! означает 1*3*5*...*n для нечетного n и
// 2*4*6*...*n для четного n. Для заданного n вычислить n!!
// OPT:Сделать цикл без if и %
#include <iostream>

int factorial(bool positive, int d, int startNumber, int n);

int main()
{
    int n, d, result;

    printf("\n\nВведите число: ");
    scanf("%d", &n);
    bool pN = (n > 0) ? true : false;

    printf("n!! для заданного n = %d\n", result);

    return 0;
}

int factorial(bool positive, int d, int startNumber, int n)
{
    int result = startNumber;
    for (; d != n && positive; d += 2) {
        result *= d + 2;
    }
    return result;
}
