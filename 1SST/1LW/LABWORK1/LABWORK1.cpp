// LABWORK1.cpp: определяет точку входа для консольного приложения.
//

//#include "stdafx.h"
//
//
// int main()
//{
//    return 0;
//}

#include "pch.h"
#include "stdafx.h"
#include <iostream>

int main()
{
    int test; //Обьявление тестовой переменной чтобы окно консоли закрывалось
    int x, y; //Обьявление переменных
    printf("Input x and y: "); //Ожидание ввода переменных х и у
    scanf_s("%d %d", &x, &y); //Ввод х и у
    printf("%d + %d = %d", x, y, x + y); //Сложение х и у и вывод их в консоль
    scanf_s("%d", &test); //Ожидание ввода переменной test
    return 0; //Остановка программы
}
