// Описать функцию вычисления корней квадратного уравнения. Функция должна возвращать количество корней, сами корни возвращаются через параметры.
//TODO - показать задание
#include <iostream>
#include <cmath>
int numberRootEquation(int a, int b, int c, float &firstRoot, float &secondRoot);

int main()
{
    printf("\n\nВведите а,b,c в квадратном уравнении через пробел: ");
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    float froot, sroot;
    int numberRoots = numberRootEquation(a, b, c, froot, sroot);

    if (numberRoots == 0)
        printf("Уравнение не имеет корней\n");
    else if (numberRoots == 1)
        printf("Количество корней уравнения = %d\n1 корень = %.2f\n", numberRoots, froot);
    else
        printf("Количество корней уравнения = %d\n1 корень = %.2f\n2 корень = %.2f\n", numberRoots, froot, sroot);

    return 0;
}

int numberRootEquation(int a, int b, int c, float &firstRoot, float &secondRoot)
{
    int numberRootEquation;
    float bFl = b, cFl = c, aFl = a;

    if (a == 0)
    {
        if (b == 0)
        {
            firstRoot = 0;
            secondRoot = 0;
            return -1;
        }
        firstRoot = (-cFl) / bFl;
        secondRoot = firstRoot;
        return 1;
    }
    else
    {
        float D = pow(bFl, 2) - 4 * aFl * cFl;
        if (D < __FLT_EPSILON__ && D > -(__FLT_EPSILON__))
        {
            firstRoot = (-bFl) / (2 * aFl);
            secondRoot = firstRoot;
            return 1;
        }
        else if (D > -__FLT_EPSILON__)
        {
            firstRoot = ((-bFl) + sqrt(D)) / (2 * aFl);
            secondRoot = ((-bFl) - sqrt(D)) / (2 * aFl);
            return 2;
        }
        else
        {
            firstRoot = 0;
            secondRoot = 0;
            return 0;
        }
    }

    return numberRootEquation;
}