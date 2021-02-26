//x принадлежит отрезку [a, b];

#include <iostream>

int main (){
    using namespace std;

    int a,b,inputNumber;
    printf("\n\nВведите границы промежутка [a,b], а также любое число. Пример ввода: 1 2 3\n");
    scanf("%d %d %d",&a,&b,&inputNumber);

    // Проверка принадлежности числа к промежутку с помощью тернарного оператора.
    (inputNumber >= a && inputNumber <= b ) ? printf("True\n\n\n") : printf("False\n\n\n");

    return 0;
}