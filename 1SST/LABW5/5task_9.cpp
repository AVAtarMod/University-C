// В трехзначном числе зачеркнули первую цифру слева. Когда полученное двузначное
// число умножили на 7, то получили данное число. Найти это число.

#include <iostream>

int main(){
    int result,num = 100;
    for (;num < 1000;num++){
        int remainder = num % 100;
        if (remainder * 7 == num){
            result = num;
        }
    }
    printf("\n\nЧисло, соответствующее условиям = %d\n",result);
    return 0;
}