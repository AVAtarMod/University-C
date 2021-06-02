//целое k делится на 7;

#include <iostream>
#include <math.h>

int main(){

    using namespace std;
    int k;
    printf("\n\nВведите число k: ");
    scanf("%d",&k);
    
    float div = fmod(k,7);
    (div == 0) ? printf("\nTrue\n\n") : printf("\nFalse\n\n");

    /*После ввода числа проверка на то, что остаток от деления этого
      числа на 7 равен 0 с помощью тернарного оператора*/

    return 0;
}