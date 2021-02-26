//уравнение ax^2 + bx + c = 0 (a != 0) не имеет действительных корней;

#include <iostream>
#include <math.h>

int main(){
    using namespace std;
    int a,b,c,D;
    printf("\n\nВведите a,b,c через пробел (a не может быть 0).Пример: 1 2 3\n");
    scanf("%d %d %d",&a,&b,&c);

    D = pow(b,2) + 4 * a * c;
    ( a != 0 && D < 0) ? printf("\nTrue\n\n") : printf("\nFalse\n\n");

    /*
    После ввода данных происходит вычисление дискриминанта уравнения, проверка
    условий с помошью тернарного оператора и вывод результата
    */
    return 0;
}