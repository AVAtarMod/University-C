// Дано число. Написать функцию поиска:а)максимальной цифры и ее позиции в числе; б)минимальной нечетной цифры и ее позиции в числе

#include <iostream>

void maxDigitAndItPosition(int& number, int& storagePosition);
void minOddDigitAndItPosition(int& number, int& storagePosition);
bool isGreatest(int firstNumber, int secondNumber);
bool isLessAndOdd(int firstNumber, int secondNumber);
void searcherDigits(int& number, int& storagePosition, bool comparator(int firstNumber, int secondNumber));

int main()
{

    printf("\n\nВведите число: ");
    int number;
    scanf("%d", &number);

    int storagePosition;
    int responseFromFunction = number;
    maxDigitAndItPosition(responseFromFunction, storagePosition);
    printf("а) Максимальная цифра = %d, её позиция = %d в числе %d\n", responseFromFunction, storagePosition, number);

    storagePosition = 0;
    responseFromFunction = number;
    minOddDigitAndItPosition(responseFromFunction, storagePosition);

    if (!storagePosition)
        printf("б) В %d нет нечетных цифр\n\n", number);
    else
        printf("б) Минимальная нечетная цифра = %d, ее позиция = %d в числе %d\n\n", responseFromFunction, storagePosition, number);
}

void maxDigitAndItPosition(int& number, int& storagePosition)
{
    searcherDigits(number, storagePosition, isGreatest);
}
void minOddDigitAndItPosition(int& number, int& storagePosition)
{
    searcherDigits(number, storagePosition, isLessAndOdd);
}

void searcherDigits(int& number, int& storagePosition, bool comparator(int firstNumber, int secondNumber))
{
    for (int numberInFor = number, previousDigit = 0, counter = 1; numberInFor > 0; numberInFor /= 10, counter++) {
        if (comparator == isLessAndOdd)
            previousDigit = 10;

        int currentDigit = numberInFor % 10;
        if (comparator(currentDigit, previousDigit)) {
            previousDigit = currentDigit;
            storagePosition = counter;
            number = currentDigit;
        }
    }
}

bool isGreatest(int firstNumber, int secondNumber)
{
    return (firstNumber >= secondNumber);
}
bool isLessAndOdd(int firstNumber, int secondNumber)
{
    return (firstNumber <= secondNumber && firstNumber % 2 == 1);
}