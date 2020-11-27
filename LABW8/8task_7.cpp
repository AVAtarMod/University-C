// Лесенкой   называется   набор   кубиков, в котором  каждый  более  верхний  слой содержит кубиков меньше, чем предыдущий. Требуется написать программу, вычисляющую число лесенок, которое можно построить из N кубиков (1 ≤ N≤ 100)

#include <iostream>
typedef int blocks;
int computeNumberStairs(blocks n, int layer);

int main(){
    std::cout << computeNumberStairs(10,1);
}

int computeNumberStairs(blocks n, int layer)
{
    if (n <= 0)
        return 0;
    int result = 0;

  int count = 0;
  for (int level = 1; level < layer; ++level) {
    if ((n - level) < 0) 
      break;
    count += computeNumberStairs(level, n - level);
  }

    return result;
}