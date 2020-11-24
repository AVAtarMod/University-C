#include <iostream>
#include "main.h"

int main(){
    printf("Выберите задачу для запуска:\n(1 or 2) :");

    int change;
    scanf("%d",&change);
    switch (change)
    {
    case 1 : l7_t3::main();
        break;
    // case 2 : l2_t2::main();
    //     break;
    
    default: printf("\nКоманда введена неверно!");
        break;
    }
    
    return 0;
}