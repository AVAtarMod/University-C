// Дано натуральное число. Написать функцию вычисления количества делителей.Найти трехзначное число с наибольшим количеством делителей. Если таких чисел несколько, то выбрать наибольшее

#include <iostream>
int numberDivisors(int number);

int main()
{
    int numberWithMaxNumberDivision;

    int previousNumberDivisors = 0;
    for (int three_digitNumber = 100; three_digitNumber < 1000; three_digitNumber++) {
        if (numberDivisors(three_digitNumber) >= previousNumberDivisors) {
            previousNumberDivisors = numberDivisors(three_digitNumber);
            numberWithMaxNumberDivision = three_digitNumber;
        }
    }
    printf("\n\nРезультат: %d\n", numberWithMaxNumberDivision);

    return 0;
}

int numberDivisors(int number)
{
    int numberDivisors = 0;

    for (int divider = 1; divider <= number; divider++)
        if (number % divider == 0)
            numberDivisors++;

    return numberDivisors;
}