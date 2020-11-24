// Написать функцию вычисления значения функции 𝑓𝑓(𝑥𝑥)=�ln(𝑥𝑥+5)𝑒𝑒𝑥𝑥−1. Вывести все значения на промежутке [A; B] с шагом h.

#include <iostream>
#include <cmath>
#include "/home/grigory/Programming/C++/Laboratory/main.h"
float fx(float number); //f(x)=sqrt( ln(x+5) / ((e^x)-1) )

int main()
{
    printf("\n\nВведите границы промежутка и шаг через пробел: ");
    float leftLimit, rightLimit, step;
    scanf("%f %f %f", &leftLimit, &rightLimit, &step);
    if (leftLimit > rightLimit)
        l7_t7::swap(leftLimit, rightLimit);

    float result;
    for (; leftLimit <= rightLimit; leftLimit += step)
    {
        result = fx(leftLimit);
        if (!(std::isnormal(result)))
            printf("В точке %.1f некорректное значение\n", leftLimit);
        else
            printf("%.3f в точке %.1f\n", result, leftLimit);
    }
    return 0;
}

float fx(float number)
{
    return sqrt(log2f(number + 5) / (pow(exp(1), number) - 1));
}