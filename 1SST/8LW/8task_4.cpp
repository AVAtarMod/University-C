// Написать функцию, вычисляющую n-ый член последовательности {Bn}.0,100BA,11122nnnnnnBABBAAПеред тестированием программы вычислить первые 10значений вручную

#include <iostream>

long int computeMemberSequenceA(long int numberMember);
long int computeMemberSequenceB(long int numberMember);

int main()
{
    printf("\n\nВведите номер(а) последовательности,-1 для выхода: ");
    long int number, result;

    while (number != -1) {
        scanf("%ld", &number);
        if (number != -1) {
            result = computeMemberSequenceB(number);
            printf("№%ld = %ld ", number, result);
            if (result == 0)
                printf("(Переполнение типа данных)\n");
            else
                printf("\n");
        }
    }
}

long int computeMemberSequenceA(long int numberMember)
{
    if (numberMember == 0)
        return 1;
    else
        return (2 * computeMemberSequenceA(numberMember - 1)) - computeMemberSequenceB(numberMember - 1);
}

long int computeMemberSequenceB(long int numberMember)
{
    if (numberMember == 0)
        return 0;
    else
        return computeMemberSequenceA(numberMember) + 2 * computeMemberSequenceB(numberMember - 1);
}
