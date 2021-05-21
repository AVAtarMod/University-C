/*сумма первых двух цифр заданного четырехзначного числа равна сумме двух
его последних цифр;*/

#include <iostream>
#include <math.h>

int main(){

    using namespace std;
    int number;
    printf("\n\nВведите четырехзначное число: ");
    scanf("%d",&number);

    if (number > 999 && number < 10000)
    {
        int thousand = number / 1000;
        int hundred = (number - (thousand * 1000) ) / 100;
        int ten = (number - (thousand * 1000) - (hundred * 100) ) / 10;
        int one = number - (thousand * 1000) - (hundred * 100) - (ten * 10);

        ((thousand + hundred) == (ten + one)) ? printf("\nTrue\n\n") : printf("\nFalse\n\n");
        
        /* Последовательное получение значений разрядов числа - от тысяч к еденицам;
        последующее сравнение (с помошью тернарного оператора) суммы тысяч и сотен
        с десятками и еденицами (т.е 1 и 2 с 3 и 4 цифрами соответственно)
        */
    }
    else
    {
        printf("\nОШИБКА:Число не четырехзначное\n\n");
    } // Если число не четырехзначное, т.е меньше 1000 или больше 9999,то выводится ошибка
    

    return 0;
}