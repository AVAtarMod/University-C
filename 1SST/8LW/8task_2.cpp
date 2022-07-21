// Пусть задано  некоторое число n. Вычислим у него сумму цифр S(n), потом сумму  цифр  получившегося  числа S(S(n))  и  так  далее,  пока  не  получится однозначное число –цифровой корень.Написать рекурсивную функцию, вычисляющую цифровой кореньПример. Найдем цифровой корень числа 95283769. S(95283769)=49, S(49)=13

#include <iostream>

int computeDigitalRoot(long int number);

int main()
{
    printf("\n\nВведите число: ");
    int number;
    scanf("%d", &number);

    int digitalRoot = computeDigitalRoot(number);

    printf("Его цифровой корень = %d\n\n", digitalRoot);
}

int computeDigitalRoot(long int number)
{
    int sumDigits = 0;
    for (int i = number; i != 0; i /= 10) {
        sumDigits += i % 10;
    }

    if (sumDigits > 10)
        return computeDigitalRoot(sumDigits);
    else
        return sumDigits;
}