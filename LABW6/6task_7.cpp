// Даны  натуральные  числа а, b (а<b).  Получить  все  простые  числа р, удовлетворяющие неравенствам: а≤р≤b.

#include <iostream>

int main(){
    int a,b;

    printf("Введите числа a b: ");
    scanf("%d %d",&a,&b);

    for (; a < b+1; a++)
    {
        int sumdiv = 0;
        for (int div = 2; div < a; div++)
        {
            if (a%div == 0)
            {
                sumdiv += div;
            }
        }
        if (sumdiv == 0)
            printf("%d  ",a);
    }
    printf("\n");

    return 0;
}