// Найти сумму целых положительных чисел, больших 20, меньших 100, кратных 3 и
// заканчивающимся на цифры 2,4 или 8.

#include <iostream>

int main(){
    int sum = 0;

    for(int num = 21;num < 100;num++){
        if ((num % 3 == 0 && (num % 10 == 2 || num % 10 == 4 || num % 10 == 8)))
        {
            sum += num;
            printf("%d;",num);
        }
    }
    printf("\n\nСумма чисел, соответствующих условиям = %d\n",sum);

    return 0;
}