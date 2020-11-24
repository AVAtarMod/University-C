#include <iostream>
#include <math.h>

int main(){

    using namespace std;
    float y1,x1,y2,x2;  // Инициализация переменных координат точек
    float A[2]={x1,y1}; // Инициализация переменной А (точки А)
    float B[2]={x2,y2}; // Инициализация переменной В (точки В)

    printf("\n\n\nВведите координаты точки А в формате x y, например 10 -2\n");
    scanf("%f %f",&x1,&y1);

    printf("Введите координаты точки B в формате x y, например 10 -2\n");
    scanf("%f %f",&x2,&y2);

    float lenght = sqrt(pow(x2-x1,2)+pow(y2-y1,2)); //Вычисление длины отрезка
    float pointMiddle[2] = { (x1+x2)/2, (y1+y2)/2 }; //Вычисление координат средней точки

    printf("1)Длина отрезка АВ = %f \n2)Координаты середины отрезка АВ:х=%f у=%f\n\n",lenght,pointMiddle[0],pointMiddle[1]);

    return 0;
}