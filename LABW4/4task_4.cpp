// Поменять местами наибольшую и наименьшую цифры числа, учитывая, что все
// цифры различны.

#include <iostream>

int main(){

    unsigned long long int start_p = 1, result, num;
    int counter = 0, max_d = 0, min_d = 10, place_min_d, place_max_d;
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
    unsigned long long int s_sp = start_p,tempNum = num;
    short int digit;

    while (start_p != 1)
    {
        start_p /= 10;

        digit = (tempNum - (tempNum % start_p) ) / start_p ;

        if (digit > max_d)
        {
            max_d = digit;
            place_max_d = start_p;
        }

        if (digit < min_d)
        {
            min_d = digit;
            place_min_d = start_p;
        }
        
        tempNum -= digit * start_p; // "Стираем" старший разряд
    }
        /* 
        Инициализация массива (с количеством элементов = числу
        разрядов). Затем помощью цикла последовательно, итерация
        за итерацией определяем цифру в кажом разряде
        */
    
    result = num - (max_d * place_max_d) + (min_d * place_max_d);
    result = result - (min_d * place_min_d) + (max_d * place_min_d);

    std::cout << "\nНовое число = " << result << "\n\n";
    
    return 0;
}