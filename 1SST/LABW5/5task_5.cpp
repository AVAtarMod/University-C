// Написать программу поиска двузначных чисел, таких, что если к сумме цифр этого
// числа прибавить квадрат этой суммы, то получится это число.

#include <iostream>

int main(){
    int n = 10,count = 0;
    printf("\nЧисла, соответствующие условиям = ");

    for(;n < 100;n++){
        int ten = n / 10;
        int one = n - (ten * 10);
        int sum = ten + one + (ten + one) * (ten + one);

        if (sum == n){
            printf("%d;",n);
            count++;
        }
    }
    printf("\n\n -- Общее количество чисел = %d --\n",count);

    return 0;
}