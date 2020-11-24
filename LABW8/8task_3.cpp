// Написать    рекурсивную    функцию,    вычисляющую n-ый    член последовательности целых чисел An.A0=2, A1=–1,An=–An-1∙An-2Перед тестированием программы вычислить первые 10значений вручную.

#include <iostream>
long int computeMemberSequence(int numberMember);

int main()
{
    printf("\n\nВведите номер(а) последовательности,-1 для выхода: ");
    long int number, result;

    while (number != -1)
    {
        scanf("%ld", &number);
        if (number != -1)
        {
            result = computeMemberSequence(number);
            printf("№%ld = %ld ", number, result);
            if (result == 0)
                printf("(Переполнение типа данных)\n");
            else
                printf("\n");
        }
    }
}

long int computeMemberSequence(int numberMember)
{
    if (numberMember == 0)
        return 2;
    else if (numberMember == 1)
        return -1;
    else
        return -(computeMemberSequence(numberMember - 1)) * computeMemberSequence(numberMember - 2);
}

