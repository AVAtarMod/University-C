// Найти сумму положительных целых чисел из промежутка от A до В, кратных 4
// (значения переменных А и B вводятся с клавиатуры).

#include <iostream>

int main()
{
    int a, b, num, sum = 0, result;

    printf("\n\nВведите А и B через пробел,например 1 4: ");
    scanf("%d %d", &a, &b);

    num = (a > b) ? b : a;
    result = (a > b) ? a : b;
    for (; num <= result; num++)
        if (num % 4 == 0 && num > 0)
            sum += num;
    printf("\nСумма чисел, соответствующих условиям = %d", sum);
    return 0;
}
