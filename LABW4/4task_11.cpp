// Составить программу, печатающую для данного натурального числа k-ую цифру
// последовательности:
// a) 12345678910..., в которой выписаны подряд все натуральные числа;
// b) 14916253649..., в которой выписаны подряд квадраты всех натуральных чисел;
// c) 1123581321..., в которой выписаны подряд все числа Фибоначчи.

#include <iostream>
#include <math.h>

long long int numOfDigit(long long int a);

int main(){
    long long int k,natNumbers = 0,squareNumbers = 0,fibNumbers = 0;

    printf("\n\nВведите число k: ");
    scanf("%lld",&k);
    int counter=1,num = 1;

    while (numOfDigit(natNumbers) < k)
    {
        natNumbers = natNumbers*counter + num;
        num++;
        counter = pow(10,numOfDigit(num));
    }
    std::cout << natNumbers << "\n";
    

    return 0;
}
long long int numOfDigit(long long int a){
    int pos = 1,sum = 0;
    while (a % pos != a)
    {
        pos *=10;
        sum ++;
    }
    sum = (a == 0) ? 1 : sum;
    return sum;
}