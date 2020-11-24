// Составить программу, позволяющую пользователю вводить с клавиатуры целые числа,
// пока не нарушается возрастание этой последовательности или пока пользователь не
// введет число, равное 100.

#include <iostream>

int main(){

    int userNumber, prevUserNumber, exit = 100;
    bool c = false;

    printf("Введите последовательность чисел (или 100 для выхода):");
    scanf("%d",&userNumber);

    while (userNumber != exit && prevUserNumber <= userNumber)
    {
        prevUserNumber = (c) ? userNumber : userNumber - 1;
        if (!c) c = true;
        
        scanf("%d",&userNumber);
    }

    return 0;
}