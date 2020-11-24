// Даны натуральные числа m и n. Найти такие натуральные р и q, не имеющие общих
// делителей, что p/q = m/n (т.е. выполнить сокращение дроби).

// (задание немного неккоректно, т.к у любого натурального числа будут общие делители)
#include <iostream>

int main(){

    int num1,num2,signal;
    printf("\n\nЕсть дробь a/b\nВведите а: ");
    scanf("%d",&num1);
    printf("Введите b: ");
    scanf("%d",&num2);

    //Если 2 число меньше 1,то поменяем их местами чтобы корректно
    //вычислить GCD
    if (num2 < num1)
    {
        int t = num2;
        num2 = num1;
        num1 = t;
        signal = 1;
    }

    //Находим НОД чисел (the Greatest Common Divider)
    int sNum2 = num2,GCD = num1;
    while (sNum2 % GCD != 0)
    {
        int t = GCD;
        GCD = sNum2 % GCD;
        sNum2 = t;
    }
    
    int t = num1;
    num1 = (signal == 1) ? (num2 / GCD) : (num1 / GCD);
    num2 = (signal == 1) ? (t / GCD) : (num2 / GCD);

    if (num2 == 1)
    {
        printf("Сокращенная дробь: %d\n",num1);
    }
    else
    {
        printf("Сокращенная дробь: %d/%d\n",num1,num2);
    }
    return 0;
}