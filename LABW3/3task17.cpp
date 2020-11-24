//натуральное n является полным квадратом;

#include <iostream>
#include <math.h>

int main(){

    using namespace std;
    int n;
    printf("\n\nВведите число n: ");
    scanf("%d",&n);
    
    ( (n > 0) && (floor(sqrt(n)) * floor(sqrt(n)) == n) ) ? printf("\nTrue\n\n") : printf("\nFalse\n\n");

    /*После ввода числа проверка на то, что число натуральное,является 
    полным квадратом и вывод результата с помощью тернарного оператора*/

    return 0;
}