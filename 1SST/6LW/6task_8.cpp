// Даны натуральные числа n и m. Найти все пары дружественных чисел, лежащих в диапазоне от n до m. Два числа называются дружественными, если каждое из них равно  сумме  всех  делителей  другого  (само  число  в  качестве  делителя  не рассматривается)
#include <cstdio>
#include <ctime>
#include <iostream>

void computing();

int main()
{
    std::clock_t start;
    double duration;
    start = std::clock();

    computing();

    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    std::cout << "Скорость выполнения: " << duration << '\n';
    return 0;
}

void computing()
{
    int n, limit, pn1 = 0, pn2 = 0;
    short int c = 0;
    bool wasmv = false;

    printf("\n\nВведите числа n m: ");
    scanf("%d %d", &n, &limit);

    // Do n less than m
    if (n > limit) {
        int mv = n;
        n = limit;
        limit = mv;
        wasmv = true;
    }
    const int saveN = n;

    for (; n <= limit, n > 0, limit > 0; n++) {
        int SODn = 0;
        for (int d = 1; d < n; d++)
            if (n % d == 0)
                SODn += d;

        int n2 = (SODn >= saveN && SODn < limit) ? SODn : 0;

        int SODn2 = 0; // sum of divider n2
        for (int d2 = 1; d2 < n2; d2++)
            if (n2 % d2 == 0)
                SODn2 += d2;

        //(n == SODn2 && n2 == SODn && n != n2 && (pn2 != n && pn1 != n2))
        if (!(n - SODn2) && !(n2 - SODn) && n - n2 && (pn2 - n && pn1 - n2)) {
            printf("%d и %d; ", n, n2);
            c++;
            if (c % 4 == 0)
                printf("\n");
            pn1 = n;
            pn2 = n2;
        }
    }

    if (wasmv == true) {
        int mv = saveN;
        n = limit;
        limit = mv;
    }
    printf("\n******\nНайдено %d пар дружественных чисел в промежутке от %d до %d\n", c, saveN, limit);
}