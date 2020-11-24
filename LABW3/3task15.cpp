//цифра 5 входит в запись трехзначного числа k;

#include <iostream>
#include <math.h>

int main(){

    using namespace std;
    int k,result;    //Инициализация переменных

    printf("\n\nВведите трехзначное число k: ");
    scanf("%d",&k); //Вывод текста и считывание ответа в виде целого числа

    if (k > 99 && k < 1000)
    {
        int hundred = k / 100;
        int ten = (k - (hundred * 100)) / 10;
        int unit = k - (hundred * 100) - (ten * 10);

        if (hundred == 5 || ten == 5 || unit == 5) printf("\nTrue\n\n");
        else printf("\nFalse\n\n");
    } 
        /*  
        Проверка числа на трехзначность
        */
    else
    {
        printf("\nОШИБКА:Число не трехзначное\n\n");
    } // Если число не трехзначное, т.е меньше 100 или больше 999,то выводится ошибка
    
    return 0;
}
    