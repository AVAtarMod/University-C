//ферзь, расположенный на поле (x1, y1) шахматной доски, «бьет» поле
//(x2, y2);

#include <iostream>

int main(){

    int x1,y1,x2,y2;
    printf("\n\nВведите координаты х и у ферзя (через пробел)\nПример:1 2\n");
    scanf("%d %d",&x1,&y1);

    printf("\nОтлично!\nТеперь введите координаты х и у поля (через пробел)\nПример:1 2\n");
    scanf("%d %d",&x2,&y2);

    int next = 0;
    next = ( (x1 > 0 && x1 < 9) && (y1 > 0 && y1 < 9) ) ? next+1 : 0;
    next = ( (x2 > 0 && x2 < 9) && (y2 > 0 && y2 < 9) ) ? next+1 : 0;

    if (next == 2)
    {
        if (x1 == x2 || y1 == y2 || ( x1 - x2 == y1 - y2 || (x1 - x2 )*-1 == y1 - y2) )
        {
            printf("\nTrue\n\n");
        }
        else
        {
            printf("\nFalse\n\n");
        }
    }
    else{
        printf("\nОШИБКА:координаты должны быть числами от 1 до 8\n");
    }

    /*
    После ввода данных проверка чисел на то,что они входят в промежуток от 1 до 8,
    затем последующая проверка координат на соответствие условиям
    с последующим выводом результата
    */
    return 0;
}