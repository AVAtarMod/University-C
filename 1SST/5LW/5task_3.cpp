// Составить программу вычисления суммы кубов чисел от 25 до 125.

#include <iostream>

int main()
{
    int n = 25, sum = 0;
    for (; n < 126; n++) {
        sum += n * n * n;
    }
    printf("\n\nСумма кубов чисел от 25 до 125 = %d\n", sum);

    return 0;
}