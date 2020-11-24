// Составить  программу  для  нахождения  всех  натуральных  решений  уравнения n2+m2=k2 в  интервале  [1,10]. Примечание:  решения,  которые  получаются перестановкой n и m, считать совпадающими.
#include <iostream>

int main(){
    int c=0,startWithoutDuplicate=1;
    printf("Решения уравнения:\n(n m k) ");
    for (int n = 1; n < 11; n++)
    {   
        for (int m = startWithoutDuplicate; m < 11; m++)
            for (int k = 1; k < 11; k++)
                if (n*n + m*m == k*k)
                { 
                    printf("(%d %d %d) ",n,m,k);
                    c++;
                    if(c%3==0) printf("\n");
                }
        startWithoutDuplicate++;
    }
    printf("\n");

    return 0;
}