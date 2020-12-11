// Известна текущая дата. Пользователь вводит день, месяц и год своего
// рождения. Написать программу, определяющую:
// a) нужно ли пользователю получать паспорт в РФ;
// b) можно ли пользователю получать права в РФ;
// c) можно ли пользователю быть выбранным в Государственную Думу РФ.
// В случае дня рождения программа должна писать поздравление.
//OPT: Показать задание А.Н
#include <iostream>
#include <ctime>

int main()
{

    using namespace std;
    int day, month, year;
    printf("Введите дату рождения в формате ДД.ММ.ГГГГ, например 06.01.2021\n");
    scanf("%d.%d.%d", &day, &month, &year);

    time_t now = time(nullptr);
    struct tm tm = *localtime(&now);

    short int nowYear = tm.tm_year + 1900;
    int nowMonth = tm.tm_mon + 1,
        nowDay = tm.tm_mday;

    int dt = (nowYear * 365 + nowMonth * 30 + nowDay) - (year * 365 + month * 30 + day);
    if (dt > 0)
    {
        int diffYear = (nowMonth < month || (nowDay > day && nowMonth == month)) ? nowYear - year : nowYear - year - 1;
        if (dt % 365 == 0)
        {
            printf("С Днем рождения!\n\n");
        }
        if (diffYear >= 13 && diffYear < 18)
        {
            printf("Вам нужно получить паспорт\n");

        }
        else if (diffYear >= 18 && diffYear < 21)
        {
            printf("Вы можете получить права в РФ\n");
            if (diffYear == 20)
            {
                printf("Вам нужно получить паспорт\n");
            }
        }
        else
        {
            printf("Вы можете получить права в РФ\nВы можете быть избраны в Государственную думу РФ\n");
            if (diffYear == 45)
            {
                printf("Вам нужно получить паспорт\n");
            }
        }
    }
    else
    {
        printf("...\nОшибка: дата неверно введена, день рождения не может быть позже текущей даты\n\n");
    }
    /*
    Вычисление возраста пользователя в годах, с последующей обработкой
    на соответвие условиям. Вывод результата.
    (Совместное использование оператора выбора, тернарного оператора 
    и операторов if/else)
    */

    return 0;
}