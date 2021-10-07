// Дано натуральное число. Написать функцию, находящую наименьший простой делитель этого числа. Используя данную функцию, разложить заданное число на множители.

#include <iostream>
#include "7task3.h"
int minimalSimpleDivisor(int number);

int main(){
    printf("\n\nВведите число: ");
    int number;
    scanf("%d",&number);

    printf("Число %d можно представить как ",number);
    if (number == 1) printf ("1   ");
    else {
        int const Number = number;
        for ( int result = 1, currentDivisor; result != Number; result *= currentDivisor, number /= currentDivisor ){
            currentDivisor = minimalSimpleDivisor(number);
            printf ("%d * ", currentDivisor);
        }
    }
    printf("\b\b\b. \n");

    return 0;
}

int minimalSimpleDivisor(int number){
    int minimalSimpleDivisor = 0;
    
    for (int divisor = 1;!minimalSimpleDivisor; divisor++)
        if (number%divisor == 0 && l7_t3ns::isSimple(divisor)){ minimalSimpleDivisor = divisor;
        }
    
    return minimalSimpleDivisor;
}