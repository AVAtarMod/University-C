// Сумма цифр трехзначного числа кратна 7, само число также делится на 7. Найти все
// такие числа.

#include <iostream>

int main(){
    int result,count = 0;

    printf("\nЧисла, соответствующие условиям = ");
    
    for (int num=100;num < 1000;num++){
        int hundred = num / 100;
        int ten = num - (hundred * 100) / 10;
        int one = num - (hundred * 100) - (ten * 10);
        int sum = hundred + ten + one;
        
        if (sum % 7 == 0 && num % 7 == 0){
            printf("%d;",num);
            count++;
            if (count == 10)
            {
                printf("\n");
            }
            
        }
        num++;
    }
    printf("\n\n -- Общее количество чисел = %d --\n",count);
    return 0;
}