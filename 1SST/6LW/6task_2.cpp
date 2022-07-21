// (Старинная задача) Сколько можно купить быков, коров и телят, если плата за быка
// 10 рублей, за корову – 5 рублей, за теленка - полтинник (0.5 рубля), если на 100
// рублей надо купить 100 голов скота.

#include <iostream>

int main()
{
    int bull, cow, youngCow;
    for (int bulls = 0; bulls < 12; bulls++) {
        for (int cows = 0; cows < 21; cows++) {
            for (int youngCows = 0; youngCows < 200; youngCows++) {
                float price = bulls * 10 + cows * 5 + youngCows * 0.5;
                if (price == 100 && bulls + cows + youngCows == 100) {
                    bull = bulls;
                    cow = cows;
                    youngCow = youngCows;
                }
            }
        }
    }
    printf("На 100 рублей можно купить %d быкa, %d коров, %d телят\n\n", bull, cow, youngCow);

    return 0;
}