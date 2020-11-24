// Числа Фибоначчи (f n ) определяются формулами: f 0 = f 1 = l; f n = f n-1 + f n-2 при n = 2, 3,...
// Составить программу
// a) определения 40-го число Фибоначчи;
// b) поиска первого числа Фибоначчи, большего m (m > 1, вводится с клавиатуры);
// c) вычисления s – суммы всех чисел Фибоначчи, которые не превосходят 1000.

#include <iostream>

int main(){

    int m,sum = 2,n = 2;

    printf("\n\nВведите число m: ");
    scanf("%d",&m);

    int fib,pFib,pFib2;

    //reset values temporary variables for next work
    pFib = pFib2 = 1;
    fib = pFib + pFib2;
    while (n != 40)
    {
        fib = pFib + pFib2;
        pFib2 = pFib;
        pFib = fib;
        n++;
    }
    printf("\n\na) 40 число Фиббоначи = %d",fib);
    

    //reset values temporary variables for next work
    pFib = pFib2 = 1;
    fib = pFib + pFib2;
    while (fib <= m && m > 1)
    {
        fib = pFib + pFib2;
        pFib2 = pFib;
        pFib = fib;
    }
    printf("\n\nb) Первое число Фибоначчи, большее m = %d",fib);

    //reset values temporary variables for next work
    pFib = pFib2 = 1;
    fib = pFib + pFib2;
    while (pFib + pFib2 < 1001)
    {
        fib = pFib + pFib2;
        pFib2 = pFib;
        pFib = fib;
        sum += fib;
    }
    printf("\n\nc) Сумма всех чисел Фибоначчи, которые не превосходят 1000 = %d",sum);
    return 0;
}