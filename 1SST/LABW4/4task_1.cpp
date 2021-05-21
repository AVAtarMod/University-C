// Найти сумму цифр числа, введенного пользователем с клавиатуры.

#include <iostream>

int main(){

    long long int num, start_p = 1;
    int counter = 0,result = 0;
    printf("\n\nВведите число, например 123 (число должно быть меньше 18 446 744 073 709 551 616): ");
    scanf("%lld",&num);

    (num < 0) ? num *= -1 : num=num;

    while (num % start_p != num)
    {
        start_p *= 10;
        counter++;
    }
        // С помощью данного цикла мы определили старший разряд

    short int counter_2 = counter - 1;

    short int digit;
    while (start_p != 1)
    {
        start_p /= 10;

        digit = (num - (num % start_p) ) / start_p ;

        result += digit;
        num -= digit * start_p; // "Стираем" старший разряд
    }
        /* 
        Инициализация массива (с количеством элементов = числу
        разрядов). Затем помощью цикла последовательно, итерация
        за итерацией определяем цифру в кажом разряде
        */

    printf("\nСумма цифр числа = %d\n\n",result);
    
    return 0;
}