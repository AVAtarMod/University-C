// Даны два натуральных числа A и B  (A < B). Написать функцию, выводящую все числа из диапазона [A; B], которые делятся на свою наибольшую цифру. Для поиск наибольшей цифры числа реализовать отдельную функцию

#include <iostream>
int maxDigitInNumber(int number);

int main(){
    printf("\n\nВведите А и B через пробел: ");
    int a,b;
    scanf("%d %d",&a,&b);

    printf("Числа, соответсвующие условиям: ");
    for (; a <= b; a++)
        if (a%maxDigitInNumber(a) == 0)
            printf(" %d",a);
    printf("\n");
    return 0;
}

int maxDigitInNumber(int number){
    int maxDigitInNumber;

    for (int previousDigit=0; number > 0; number /= 10)
    {
        int currentDigit = number%10;
        if (currentDigit > previousDigit){
            previousDigit = currentDigit;
            maxDigitInNumber = currentDigit;
        }
    }

    return maxDigitInNumber;
}