// Известно, что произведение N первых нечетных чисел равно р. 
// Определить, сколько сомножителей взято. Если разложить число р на 
// сомножители не удается – вывести об этом сообщение.

#include <iostream>
#include <string>

int main(){

    int num,n,numEfficient = 0,result = 0,result2 = 1;

    printf("\n\nВведите  число :");
    scanf("%d",&num);

    while (result != num && result <= num && num > 0)
    {
        if (result==0) result++;
        result *= result2;
        result2 += 2;
        numEfficient++;
    }
    
    if (result > num)
    {
       printf("Введенное число разложить на сомножители не удалось\n\n");
    }
    else 
    {
        printf("\nКоличество сомножителей = %d\n\n",numEfficient);
    }
    return 0;
}