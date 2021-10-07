#include <iostream>
#include <math.h>
int main(){

    using namespace std;
    float degree1,degree2,degree3; //Переменные для угла №1,№2,№3
    int radius; //Переменная радиуса описанной окружности

    printf("\n\n\nВведите значение углов а,b,c треугольника в формате a b c (например 1 2 3)\n");
    scanf("%f %f %f",&degree1,&degree2,&degree3);

    if (degree1 + degree2 + degree3 == 180)
    {
        degree1 = (degree1 * M_PI) / 180 ;
        degree2 = (degree2 * M_PI) / 180 ;
        degree3 = (degree3 * M_PI) / 180 ;
        // Перевод радиан в градусы
        printf("Введите радиус описанной окружности R \nR = ");
        scanf("%d",&radius);


        float vertice1,vertice2,vertice3;
        vertice1 = 2 * radius * sin(degree1);
        vertice2 = 2 * radius * sin(degree2);
        vertice3 = 2 * radius * sin(degree3);
        // Вычисление сторон треугольника по заданной формуле
        printf("\n\nСторона А = %f \nСторона В = %f\nСторона С = %f\n\n",vertice1,vertice2,vertice3); // Вывод результата вычислений
    } 
    else
    {
        printf("\nОШИБКА:Сумма углов меньше или больше 180 градусов или значения углов\nневерно введены");
    }
    
    /* 
    Проверка введенного значения углов на правильность (их сумма = или != 180)
    */
    
}