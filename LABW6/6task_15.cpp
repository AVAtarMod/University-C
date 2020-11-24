// Найти  все  простые  несократимые  дроби,  заключенные  между  0  и  1,  знаменатели которых  не  превышают  7  (дробь  задается  двумя  натуральными  числами –числителем изнаменателем)

#include <iostream>

int main(){
    int c=0;
    printf("\n\nПростые несократимые дроби:\n");
    for (int upN = 1; upN < 7 ; upN++)
    {
        for (int downN = 1; downN < 8; downN++)
        {
            int NOD = upN;
            int del = downN;
            while (del % NOD != 0)
            {
                int t = NOD;
                NOD = del % NOD;
                del=t;
            }
            if (NOD == 1 && upN < downN){
                printf("%d/%d;  ",upN,downN);
                c++;
                if (c%6 == 0) printf("\n");
            }
        }
    }
    printf("\n");
    return 0;
}