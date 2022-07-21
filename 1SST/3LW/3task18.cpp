//даны три произвольные числа. Длины отрезков, заданные этими числами,
//являются сторонами треугольника;

#include <iostream>

int main()
{
    using namespace std;

    int lenght1, lenght2, lenght3;
    printf("\n\nВведите длины отрезков через пробел.Пример: 1 2 3\n");
    scanf("%d %d %d", &lenght1, &lenght2, &lenght3);

    if ((lenght1 + lenght2 > lenght3) && (lenght2 + lenght3 > lenght1) && (lenght1 + lenght3 > lenght2)) {
        printf("\nTrue\n\n");
    } else {
        printf("\nFalse\n\n");
    }
    /* После ввода длин отрезков проверка на то,что сумма каждой из 2
    сторон больше длины 3. Если для всех сторон это условие верно,
    значит искомая фигура является треугольником
    */

    return 0;
}