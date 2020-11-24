//Поменять местами первую и последнюю цифры числа.

#include <iostream>

int main(){

    unsigned long long int num, start_p = 1, s_sp;
    int counter = 0,result = 0;
    printf("\n\nВведите число, например 123 (число должно быть меньше 18 446 744 073 709 551 616): ");
    scanf("%lld",&num);

    (num < 0) ? num *= -1 : num=num;

    // С помощью данного цикла мы определим старший разряд
    while (num % start_p != num)
    {
        start_p *= 10;
        counter++;
    }
    
    short int counter_2 = counter - 1;
    s_sp = start_p,result = num; // result используется как временная переменная

    short int digit,firstDigit,lastDigit;
    while (start_p != 1)
    {
        start_p /= 10;

        digit = (result - (result % start_p) ) / start_p ;
        
        firstDigit = (start_p*10 == s_sp) ? digit : firstDigit;
        lastDigit = (start_p == 1) ? digit : lastDigit;

        result -= digit * start_p; // "Стираем" старший разряд
        counter_2--;
        
    }
    result = num;
    result -= (firstDigit * s_sp / 10) - (lastDigit * s_sp / 10);
    result -= lastDigit - firstDigit;

    printf("\nНовое число = %d\n\n",result);
    return 0;
}