// Написать   программу,   вычисляющую   значение   функции   Аккермана при заданных m и n(1 ≤ m, n≤ 10).

#include <iostream>
using namespace std;

int ackerman(int m, int n);

int main()
{
    printf("Введите m и n: ");
    int m, n;
    scanf("%d %d", &m, &n);
    cout << ackerman(m, n) << endl;
}

int ackerman(int m, int n)
{
    if (m == 0) {
        return n + 1;
    } else if (n == 0) {
        return ackerman(m - 1, 1);
    } else {
        return ackerman(m - 1, ackerman(m, n - 1));
    }
    return 0;
}