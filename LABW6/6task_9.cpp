// Составить  программу  возведения  заданного  числа  в  третью  степень,  используяследующую закономерность:13=1 23=3+5 33=7+9+11 43=13+15+17+19

#include <iostream>

int startOfSequence(int n);

int main(){
    int n,result = 0;
    printf("Введите число n: ");
    scanf("%d",&n);

    int sum = startOfSequence(n);
    for (int p = 0; p < n; p++)
    {
        sum +=2;
        result += sum;
    }
    printf("%d в кубе = %d\n",n,result);
    return 0;
}

int startOfSequence(int n){
    int SOS=-1,c=0;
    for (int i = 0; i < n; i++)
    {
        c+=i;
    }
    for (int i = 0; i < c; i++)
    {
        SOS+=2;
    }
    return SOS;
}
