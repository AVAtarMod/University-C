#include <iostream>
#include <math.h>
int main()
{
    using namespace std;
    int a, x, y = 0; // Инициализация переменных а и х

    printf("\n\n\nВведите переменную a ");
    scanf("%d", &a);
    printf("Введите переменную x ");
    scanf("%d", &x);

    int temporary = abs(a * x - pow(x, 3)); // Инициализация временной переменной
    y = abs(pow(x, 5) + temporary - a) + a * pow(x, 2) + pow(a, 8);
    printf("Значение функции у=%d \n\n", y);

    return 0;
}