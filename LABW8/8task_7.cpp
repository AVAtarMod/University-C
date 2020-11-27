// Лесенкой   называется   набор   кубиков, в котором  каждый  более  верхний  слой содержит кубиков меньше, чем предыдущий. Требуется написать программу, вычисляющую число лесенок, которое можно построить из N кубиков (1 ≤ N≤ 100)

#include <iostream>
using namespace std;
typedef int blocks;

void stairs(int numberLayer, blocks n);
int d = 0;

int main()
{
    blocks n;
    cout << "Введите количество кубиков: ";
    cin >> n;
    if (n > 0 && n < 101)
    {
        stairs(1, n);
    }
    cout << "Количество лесенок = " << d - 1 << "\n";
    return 0;
}
//В результате считает количество возможных 1 слоев с N-1 кубиками
void stairs(int numberLayer, blocks n)
{
    if (n == 0)
    {
        d++;
    }
    for (int i = numberLayer; i <= n; i++)
    {
        stairs(i + 1, n - i);
    }
}