// Найти натуральное число от 1 до 10000 с максимальной суммой делителей.

#include <iostream>

int main()
{
    int result;
    for (int num = 1, pastSOD = 1; num < 10001; num++) {
        int curSOD = 0; // current sum of divider
        for (int d = 1; d < num + 1; d++) {
            if (num % d == 0) {
                curSOD += d;
            }
        }
        if (curSOD > pastSOD) {
            result = num;
            pastSOD = curSOD;
        }
    }
    printf("\n\nРезультат = %d\n", result);

    return 0;
}