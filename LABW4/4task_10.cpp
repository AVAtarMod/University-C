// Найти наименьшее общее кратное (НОК) чисел n и m, если
// HOK(n,m) = n*m / НОД(n,m)

#include <iostream>

int main(){
    int num1,num2,result;
    printf("\n\nВведите 2 числа через пробел:");
    scanf("%d %d",&num1,&num2);

    //Если 2 число больше 1,то поменяем их местами
    if (num2 > num1)
    {
        int t = num2;
        num2 = num1;
        num1 = t;
    }

    //Находим НОД чисел
    int sNum1 = num1,sNum2 = num2;
    while (sNum1 % sNum2 != 0)
    {
        int t = sNum2;
        sNum2 = sNum1 % sNum2;
        sNum1 = t;
    }
    //Находим НОК чисел
    result = num1 * num2 / sNum2;
    printf("НОК чисел = %d\n\n",result);

    return 0;
}