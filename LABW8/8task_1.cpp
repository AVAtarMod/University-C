// Написать  рекурсивную  функцию,  выводящую  цифры  заданного  числа в обратном порядке (начиная с младших разрядов). Пример. Для числа 16543 результат должен быть следующим 34561 Изменить функцию так, чтобы цифры числа выводились, начиная со старшего разряда, каждая цифра должна находиться в своей строке.Пример. Для числа 16543 результат должен быть следующим 16543 Изменить функцию так, чтобы вместо печати цифр вычислялась сумма цифр заданного числа.

#include <iostream>
void OutputDigits(long int number);
void OutputDigits_invert(long int number);
long int computeSumDigits(long int number, int sum);

int main()
{
    printf("Введите число: ");
    long int number;
    scanf("%ld",&number);

    printf("Вывод чисел с младшего разряда: \n");
    OutputDigits(abs(number));

    printf("Теперь наоборот: \n");
    OutputDigits_invert(abs(number));
    
    int sum = computeSumDigits((abs(number)),0);
    printf("\nСумма цифр числа = %d\n\n",sum);
    return 0;
}

void OutputDigits(long int number){
    printf("%ld\n",number%10);
    if (number/10 > 0) OutputDigits(number/10);
}

void OutputDigits_invert(long int number){
    if (number > 9) OutputDigits_invert(number/10);
    printf("%ld\n",number%10);
}

long int computeSumDigits(long int number, int sum){
    if (number) return computeSumDigits(number/10,sum + number%10);
    else return sum;
}