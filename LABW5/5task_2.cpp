// Определить количество трехзначных чисел, сумма цифр которых равно заданному
// числу N.

#include <iostream>
#include <math.h>

int main(){

    int n,sum,number = 100,counter = 0;
    printf("Введите число: ");
    scanf("%d",&n);

    for (;number < 1000;number++)
    {
        int hundred = number / 100;
        int ten = (number - (hundred * 100) ) / 10;
        int one = number - (hundred * 100) - (ten * 10);
        sum = hundred + ten + one;
        if (sum ==n){
            counter+=1;
            printf("%d\n",number);
        }
    }

    printf("\nКоличество чисел, соответствующих условию - %d\n",counter);
    return 0;
}