// Даны  натуральные  числа m, n1, n2,..,,n m(m>2).  Вычислить  НОД(n1, n2,.., nm),воспользовавшисьсоотношениемНОД(n1, n2,.., nm)=НОД(НОД(n1, n2,.., nm-1), nm)иалгоритмом Евклида

#include <iostream>

int main()
{
    int m, NOD;
    printf("\n\nВведите количество чисел : ");
    scanf("%d", &m);

    int n1 = 0, n2 = 0, n3 = 0;
    for (int i = 1; i < m + 1; i++) {
        if (n1 == 0 && n2 == 0) {
            printf("Введите первые 2 числа: ");
            scanf("%d %d", &n1, &n2);
            i = 2;
            while (n1 % n2 != 0) {
                int t = n2;
                n2 = n1 % n2;
                n1 = t;
            }
        } else if (i == 3) {
            printf("Введите %d число: ", i);
            scanf("%d", &n3);
            while (n2 % n3 != 0) {
                int t = n3;
                n3 = n2 % n3;
                n2 = t;
            }
            NOD = n3;
        } else {
            printf("Введите %d число: ", i);
            scanf("%d", &n3);
            if (NOD < n3) {
                int t = n3;
                n3 = NOD;
                NOD = t;
            }
            while (NOD % n3 != 0) {
                int t = n3;
                n3 = n2 % n3;
                n2 = t;
            }
            NOD = n3;
        }
    }
    printf("Результат: %d\n", n3);
    return 0;
}
