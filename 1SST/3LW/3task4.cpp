//x лежит вне отрезка [a, b] или [c, d];

#include <iostream>

int main (){
    using namespace std;

    int a,b,c,d,inputNumber;
    printf("\n\nВведите границы промежутка [a,b],границы промежутка [c,d],\nа также любое число через пробел. Пример ввода: 1 2 3 4 5\n\n");
    scanf("%d %d %d %d %d",&a,&b,&c,&d,&inputNumber);

    // Проверка отсутствия принадлежности числа к промежуткам (хотя бы одному из них) с помощью тернарного оператора

    ( (inputNumber < a || inputNumber > b ) || (inputNumber < c || inputNumber > d) ) ? printf("True\n\n\n") : printf("False\n\n\n");

    return 0;
}