//точка (x, y) лежит вне круга радиуса r с центром в точке (1, 0);

#include <iostream>
#include <math.h>

int main(){
    using namespace std;

    float x,y,r,result;

    printf("\n\nВведите координаты точки х,у а также радиус окружности r\nРадиус окружности:");
    scanf("%f",&r);
    printf("\nКоординаты х,у (вводить через пробел, для дробной части\nиспользовать ','):");
    scanf("%f %f",&x,&y);

    ( ( pow(x - 1,2) + pow(y,2) ) > pow(r,2) ) ? printf("\nTrue\n\n") : printf("\nFalse\n\n");

    return 0;
}