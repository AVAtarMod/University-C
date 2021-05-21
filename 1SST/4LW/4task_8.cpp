// Составить программу, проверяющую, является ли заданное натуральное число
// совершенным, то есть равным сумме своих положительных делителей, кроме самого этого
// числа.

#include <iostream>

int main(){
    int num,sum = 0,div = 1;
    printf("Введите число: ");
    scanf("%d",&num);

    while (sum < num)
    {
        sum += (num % div == 0) ? div : 0 ;
        div++;
    }
    if (sum == num)
    {
        printf("Поздравляю, число совершенно =)\n\n");
    }
    
}