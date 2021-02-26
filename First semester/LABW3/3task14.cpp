/*уравнение ax^2 + bx + c = 0 , где a, b, c могут равняться 0, имеет ровно один
корень;*/

#include <iostream>
#include <math.h>

int main(){
    using namespace std;
    int a,b,c,D,x=1;
    printf("\n\nВведите a,b,c через пробел.Пример:1 2 3\n");
    scanf("%d %d %d",&a,&b,&c);
    D = b*b - 4*a*c;

    if ((a == 0 || D == 0) && (a != 0 || b != 0))
    {
        printf("True\n\n");
    }
    else
    {
        printf("False\n\n");
    }
    return 0;
}