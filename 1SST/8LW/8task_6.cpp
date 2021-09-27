// Требуется вывести все различные представления натурального числа N в виде суммы  натуральных  чисел.  Представления,  отличающиеся  друг  отдруга порядком слагаемых, не являются различными. (2 ≤ N ≤ 20)

#include <iostream>
using std::cout;
using std::endl;
unsigned long long int computeOutupDecomposition(int number, int countDecompositions, unsigned long long int lastDecomposition, ...);

int main()
{
}

unsigned long long int computeOutputDecomposition(int number, int countDecompositions, __int128_t lastDecomposition, ...)
{
    for (__int128_t *p = &lastDecomposition, c = 0; c != countDecompositions; p++, c++)
    {
        if (*p == (number * 10) + 1) return 1;
    }
    printf("\n");


}