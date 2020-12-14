#include <iostream>
#include <random>

int *getRangeUser()
{
    int *choice = new int[2];

    std::printf("Введите числа А и В диапазона [А;В] :");
    std::scanf("%d %d", &choice[0], &choice[1]);

    return choice;
}