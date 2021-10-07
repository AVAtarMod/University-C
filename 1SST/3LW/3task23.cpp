// конверт со сторонами (a, b) может войти в конверт со сторонами (c, d) или
// наоборот;

#include <iostream>

int main(){
    using namespace std;

    int a,b,c,d;
    printf("\n\nВведите стороны конвертов через пробел.Пример: 1 2 3 4\n");
    scanf("%d %d %d %d",&a,&b,&c,&d);

    int temp = a;
    a = (a < b) ? a : b;
    b = (a == b) ? temp : b;

    temp = c;
    c = (c < d) ? c : d;
    d = (c == d) ? temp : d;

    if ((a < c && b < d) || (c < a && d < b))
    {
        printf("\nTrue\n\n");
    }
    else
    {
        printf("\nFalse\n\n");
    }
    /* После ввода сторон проверка на то,что сторона 1 конверта < стороны 
    2 конверта для каждой из сторон
    */

    return 0;
}