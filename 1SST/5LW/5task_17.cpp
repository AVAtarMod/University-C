// Из диапазона целых четырехзначных чисел от n до k выбрать те, запись которых
// содержит ровно 3 одинаковых цифры. Например, 6766, 5444, 0006, 0060.

#include <iostream>

bool rightNum(int n);

int main(){
    int n,k,counter = 0;

    printf("\n\nВведите числа n и k: ");
    scanf("%d %d",&n,&k);

    if (n>k)
    {
        int temp = n;
        n = k;
        k=temp;
    }
    
    printf("\nЧисла, соответствующие условиям = \n");
    for(;n <= k;n++){
        if (n < 10000 && rightNum(n))
        {
            printf("%.4d;",n);
            counter++;

            if (counter % 8 == 0) printf("\n");
        }
    }
    printf("\n******\nБыло выведено %d чисел\n",counter);
    return 0;
}

bool rightNum(int n){
    int digit,c = 0;
    const int number = n;

    //Сделаем любое маленькое число четырехзначным
    if (n<1000)
    {
        while (n<1000)
        {
            n*=10;
        }
    }
    
    //Проверяем число на то,что есть 3 одинаковых цифры
    while (n > 0 && c != 3)
    {
        c = 0;
        digit = n%10;
        int temp = number;
        for (int i = 0; i < 4; i++)
        {
            int numMatch = temp%10;
            if (numMatch == digit) c++;
            temp /= 10;
        }
        n /= 10;
    }

    if (c == 3) return true;
    else return false;
}