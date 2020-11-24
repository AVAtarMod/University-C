//из чисел x, y и z только два равны между собой;

#include <iostream>

int main(){
    using namespace std;

    int x,y,z;
    printf("\n\nВведите х,у,z через пробел.Пример: 1 2 3\n");
    scanf("%d %d %d",&x,&y,&z);

    if ((x == y && x != z) || (x == z && x != y) || (y == z && y != x))
    {
        printf("\nTrue\n\n");
    }
    else
    {
        printf("\nFalse\n\n");
    }
    
    /*
    После ввода данных проверка числел на то,что из чисел x, y и z только два равны между собой и вывод результата.
    */
    return 0;
}