// Описать функцию вычисления корней квадратного уравнения. Функция должна возвращать количество корней, сами корни возвращаются через параметры.

#include <iostream>
#include <cmath>
int numberRootEquation(float a, float &bAndFirstRoot, float &cAndSecondRoot);

int main(){
    printf("\n\nВведите а,b,c в квадратном уравнении через пробел: ");
    float a, b, c;
    scanf ("%f %f %f", &a, &b, &c);
    int numberRoots = numberRootEquation(a,b,c);

    if ( !( std::isnormal(b)) ) numberRoots--;
    if ( !( std::isnormal(c)) ) numberRoots--;
    if (numberRoots < 0) numberRoots=0;
    
    if (!numberRoots) printf("Количество корней уравнения = %d\n", numberRoots);
    else if (b == c) printf("Количество корней уравнения = %d\n1 корень = %.2f\n", numberRoots, b);
    else printf("Количество корней уравнения = %d\n1 корень = %.2f\n2 корень = %.2f\n", numberRoots, b, c);
    
    return 0;
}

int numberRootEquation(float a, float &bAndFirstRoot, float &cAndSecondRoot){
    int numberRootEquation;
    float b = bAndFirstRoot, c = cAndSecondRoot;

    if (!a){
        bAndFirstRoot = cAndSecondRoot = (-c)/b;
        return 1;
    }

    float discriminant = sqrt(pow(bAndFirstRoot,2)-4*a*cAndSecondRoot);
    bAndFirstRoot = (-b + discriminant)/(2 * a);
    cAndSecondRoot = (-b - discriminant)/(2 * a);

    if (discriminant == 0) numberRootEquation = 1;
    if (discriminant > 0) numberRootEquation = 2;
    if (discriminant < 0) numberRootEquation = 0;

    return numberRootEquation;
}