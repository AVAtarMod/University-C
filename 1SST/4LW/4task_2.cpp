// Найти первую цифру числа.

#include <iostream>

int main()
{

    long long int num, start_p = 1;
    int counter = 0;
    short int result;
    printf("\n\nВведите число, например 123 (число должно быть меньше 18 446 744 073 709 551 616): ");
    scanf("%lld", &num);

    (num < 0) ? num *= -1 : num = num;

    while (num % start_p != num) {
        start_p *= 10;
        counter++;
    }
    // С помощью данного цикла мы определили старший разряд,"координату" 1 цифры

    result = (num - (num % (start_p / 10))) / (start_p / 10);
    printf("\nПервая цифра числа = %d\n\n", result);

    return 0;
}