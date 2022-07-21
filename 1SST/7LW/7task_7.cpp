// Написать функцию swap, меняющую местами значения двух переменных

#include <iostream>

template <typename T>
void swap(T& firstNumber, T& secondNumber);

int main()
{
    printf("\n\nВведите 2 числа: ");
    int firstNumber, secondNumber;
    scanf("%d %d", &firstNumber, &secondNumber);

    swap(firstNumber, secondNumber);

    printf("\nРезультат работы программы = %d %d\n", firstNumber, secondNumber);

    return 0;
}

template <typename T>
void swap(T& firstNumber, T& secondNumber)
{
    T buffer = firstNumber;
    firstNumber = secondNumber;
    secondNumber = buffer;
}
