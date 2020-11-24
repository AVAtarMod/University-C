// Составить  программу  получения  всех  совершенных  чисел,  меньших  заданного числа n.  Число  называется  совершенным,  если  равно  сумме всех  своих положительных делителей, кроме самого этого числа. Например, 28 -совершенно, т.к. 28=1+2+4+7+14.

#include <iostream>

int main(){
    long long int n,sum;
    printf("Введите n: ");
    scanf("%lld",&n);
    for (long long int i = 1; i < n; i++)
    {
        sum = 0;
        for (long long int pos = 1; pos < i; pos++)
        {
            if (i % pos == 0) 
            {
                sum += pos;
            }
        }
        if (sum == i) printf("%lld ",sum);
    }
    printf("\n ");
    return 0;
}