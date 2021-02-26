//x – положительное число; (здесь и далее 1 комментарий является текстом задач)

#include <iostream>

int main(){

    using namespace std;

    int inputData;

    printf("\n\nВведите число x: ");
    scanf("%d",&inputData);
    /*
    Число из переменной inputData сравнивается с 0. Если оно больше его,то выводится True,
    если нет то False
    */
    if (inputData > 0)
    {
        printf("True\n\n");
    }
    else 
    {
        printf("False\n\n");
    }
    return 0;

}