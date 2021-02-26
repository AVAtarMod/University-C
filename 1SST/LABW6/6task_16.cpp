// В данном натуральном числе переставить цифры таким образом, чтобы образовалось наименьшее число, записанное этими же цифрами

#include <iostream>

int main(){
    printf("\n\nВведите натуральное число:  ");
    int n, result=0;
    scanf("%d",&n);

    int numZ = 0;
    for (int nn = n; nn > 0; nn /=10)
        if (!(nn%10)) numZ++;
    
    int Max=0,Sp=0;
    for (int am = 1,prevMax; n > 0;am *= 10)
    {
        Sp = am;
        int max = 0;    //Find max digit
        int nn = n;     // Copying of entered number to temporary variable.
        int pos = 1,sp; // Do save of position max digit in number.
        for (int nn =n; nn != 0; pos *= 10, nn /= 10){
            int rem = nn%10;
            if (max <= rem) {
                max = rem;
                Max = rem;
                sp = pos;
            }
        }
        result += max * am;

        prevMax = max;
        n  -= max*sp;
    }

    for (; numZ != 0; --numZ,Sp *=10)
        result = result - Sp*Max + Sp*Max*10;
    
    printf("Результат - %3d\n\n",result);
    return 0;
}