// Дано натуральное число n (n < 10000). Определить, является ли оно палиндромом
// («перевертышем») с учетом четырех цифр. Например, 2222, 6116,0440.

#include <iostream>

int main()
{
    int m, counter;

    printf("\n\nВведите число: ");
    scanf("%d", &m);
    for (int n = m; n <= m; n++) {
        if (n == m) {
            int thousand = n / 1000;
            int hundred = (n - (thousand * 1000)) / 100;
            int ten = (n - (thousand * 1000) - (hundred * 100)) / 10;
            int one = n - (thousand * 1000) - (hundred * 100) - (ten * 10);
            if (thousand == one && hundred == ten && n == m) {
                printf("\n%d является палиндромом\n", m);
            }
        }
    }

    return 0;
}