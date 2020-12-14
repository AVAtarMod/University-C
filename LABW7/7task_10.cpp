// Описать функцию вычисления корней квадратного уравнения. Функция должна возвращать количество корней, сами корни возвращаются через параметры.
//TODO - показать задание
#include <iostream>
#include <cmath>
int numberRootEquation(float a, float &bAndFirstRoot, float &cAndSecondRoot);

int main()
{
    printf("\n\nВведите а,b,c в квадратном уравнении через пробел: ");
    float a, b, c;
    scanf("%f %f %f", &a, &b, &c);
    int numberRoots = numberRootEquation(a, b, c);

    if (!numberRoots)
        printf("Количество корней уравнения = %d\n", numberRoots);
    else if (b == c)
        printf("Количество корней уравнения = %d\n1 корень = %.2f\n", numberRoots, b);
    else
        printf("Количество корней уравнения = %d\n1 корень = %.2f\n2 корень = %.2f\n", numberRoots, b, c);

    return 0;
}

int numberRootEquation(float a, float &bAndFirstRoot, float &cAndSecondRoot)
{
    int numberRootEquation;
    float b = bAndFirstRoot, c = cAndSecondRoot;

    if (!a)
    {
        bAndFirstRoot = cAndSecondRoot = (-c) / b;
        return 1;
    }

    float discriminant = pow(bAndFirstRoot, 2) - 4 * a * cAndSecondRoot;
    if (discriminant == 0)
    {
        numberRootEquation = 1;
        bAndFirstRoot = (-b + discriminant) / (2 * a);
    }
    else if (discriminant > 0)
    {
        numberRootEquation = 2;
        bAndFirstRoot = (-b + discriminant) / (2 * a);
        cAndSecondRoot = (-b - discriminant) / (2 * a);
    }
    else
        numberRootEquation = 0;
        bAndFirstRoot = 0;
        cAndSecondRoot = 0;

    return numberRootEquation;
}