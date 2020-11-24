// Дано натуральное число n. Получить все его натуральные делители.

#include <iostream>

int main(){
    int n;

    printf("\n\nВведите число: ");
    scanf("%d",&n);

    printf("Натуральные делители числа %d = ",n);
    for(int d = 1;n > 0 && d <= n;d++)
        if (n % d == 0)
        {
            printf("%d;",d);
        }

    printf("\n\n");
    return 0;
}