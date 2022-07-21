//все числа x, y и z равны между собой;

#include <iostream>

int main()
{
    using namespace std;

    int x, y, z;
    printf("\n\nВведите х,у,z через пробел.Пример: 1 2 3\n");
    scanf("%d %d %d", &x, &y, &z);

    (x == y && x == z) ? printf("\nTrue\n\n") : printf("\nFalse\n\n");
    /*
    После ввода данных проверка числел на то,что они равны между собой с помощью
    тернарного оператора,и вывод результата.
    */
    return 0;
}