/* Найти все трехзначные числа, удовлетворяющие каждому из двух условий:
•любые две цифры различны;
•число  равно  среднему  арифметическому  всех  трехзначных  чисел  (включая данное), имеющих тот же цифровой состав. */
#include <cmath>
#include <iostream>

int main()
{
    int c = 0;
    printf("\n\nЧисла,соответствующие условиям:\n");
    for (int i = 100; i < 1000; i++) {
        //Разбиваем число на цифры
        int sum = 0, hrd = (i - i % 100) / 100, ten = (i % 100 - i % 10) / 10, one = i % 10;
        bool oneDef = false, twoDef = false;

        //Находим среднее арифметическое чисел,имеющих тот же цифровой состав
        int ten2, hrd2, one2;
        for (int ii = 1; ii < 7; ii++) {
            switch (ii) {
            case 1:
                one2 = 1;
                ten2 = 10;
                hrd2 = 100;
                break;
            case 2:
                one2 = 1;
                ten2 = 100;
                hrd2 = 10;
                break;
            case 3:
                one2 = 10;
                ten2 = 1;
                hrd2 = 100;
                break;
            case 4:
                one2 = 10;
                ten2 = 100;
                hrd2 = 1;
                break;
            case 5:
                one2 = 100;
                ten2 = 1;
                hrd2 = 10;
                break;
            case 6:
                one2 = 100;
                ten2 = 10;
                hrd2 = 1;
                break;

            default:
                printf("Error,ii is overarea");
                break;
            }
            sum += hrd * hrd2 + ten * ten2 + one * one2;
        }
        sum /= 6;

        if (one != hrd || one != ten)
            oneDef = true;
        if (i == sum)
            twoDef = true;

        //Вывод подходящих чисел
        if (oneDef && twoDef) {
            c++;
            printf("%d; ", i);
            if (c % 6 == 0)
                printf("\n");
        }
    }
    printf("\n******\n%d подходящих чисел\n", c);
    return 0;
}