// Написать функцию (перегрузки функции для int и  double) CompareTo, которая получает в качестве параметров два значения, и возвращает –1, если первое меньше второго, 0, если они равны, и 1, если первое больше второго. Используя данную функцию, проверить является ли функция y=x^3+sin(x ) возрастающей на промежутке [-1, 1].
//OWN: Сделать свою программу из этой

#include <iostream>
#include <cmath>
int CompareTo(int firstNumber,int secondNumber);
double CompareTo(double firstNumber,double secondNumber);
double y(float x);

int main(){
    bool increase = false;
    bool decrease = false;
    bool undefiendRise = false;

    for (float movingPoint = -1; movingPoint <= 1 && !undefiendRise; movingPoint+=__FLT_EPSILON__)
    {
        float y1 = y(movingPoint);
        float y2 = y(movingPoint+__FLT_EPSILON__);

        if (CompareTo(y1,y2) == -1) increase = true;
        if (CompareTo(y1,y2) == 1 && !increase) decrease = true;
        if (CompareTo(y1,y2) == 1 && increase){ 
            undefiendRise = true;
            increase = false;
            decrease = false;
            }
    }
    if (increase) printf("\n\nФункция y=x^3 + sin(x) возрастает на промежутке [-1, 1]\n\n");
    if (decrease) printf("\n\nФункция y=x^3 + sin(x) убывает на промежутке [-1, 1]\n\n");
    if (undefiendRise) printf("Функция y=x^3 + sin(x) ведет себя по-разному на промежутке [-1, 1]\n\n");

    return 0;
}

int CompareTo(int firstNumber,int secondNumber){
    if (firstNumber < secondNumber) return -1;
    else if (firstNumber == secondNumber) return 0;
    else return 1;
}
double CompareTo(double firstNumber,double secondNumber){
    if (firstNumber - secondNumber <= __FLT_EPSILON__) return -1;
    else if (fabs(firstNumber - secondNumber) <= __FLT_EPSILON__*fabs(firstNumber)) return 0;
    else return 1;
}

double y(float x){
    return pow(x,3) + sin(x);
}