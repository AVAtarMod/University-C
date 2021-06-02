// Найти цифровой корень числа (однозначное число, получаемое путем
// последовательного сложения цифр числа, затем цифр полученной суммы и т. д. до
// тех пор, пока не получится однозначное число).

#include <iostream>
int sumDigit(long long int a);

int main(){
    long long int n,result = 0;

    printf("\n\nВведите число: ");
    scanf("%lld",&n);

    long long int num = n;

    if (n == 0) result  = 0;
    else
    {
        //Делаем n > 0,затем суммируем цифры пока сумма не будет меньше 10
        n = (n<0) ? n*-1 : n;
        while (n > 9)
        {
            n = sumDigit(n);
        }
    }

    printf("Цифровой корень %lld = %lld\n\n",num,n);
    return 0;
}

int sumDigit(long long int a){
    int digit,sum = 0;

    while (a > 0)
    {
        long long int max_digit = 1;
        while (a % max_digit != a){
            max_digit *= 10;
        }
        max_digit /= 10;

        digit = (max_digit == 1) ? a : (a - (a % max_digit)) / max_digit;
        sum +=digit;

        a -= (a - (a % max_digit));
    }
    return sum;
}