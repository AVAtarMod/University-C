#include <iostream>
#include <fstream>
#include <sstream>

#include "stack.hpp"
#include "query.hpp"
#include "useful.hpp"
#include "LW_lib.hpp"

void task1();
void task2();
void task3();
void task4();
void task5();

int main(int argc, char const *argv[])
{
    bool noData = false;
    if (argc == 1)
    {
        printf("Введите программу для запуска: ");
        argc++;
        noData = true;
    }
    for (int i = 1; i < argc; i++)
    {
        int choice;
        if (noData)
        {
            scanf("%d", &choice);
            std::cin.ignore(32767, '\n');
        }
        else
        {
            choice = std::stoi(argv[i]);
        }

        switch (choice)
        {
        case 1:
            std::cout << "Задание №1\n";
            task1();
            std::cout << "-----\n";
            break;
        case 2:
            std::cout << "Задание №2\n";
            task2();
            std::cout << "-----\n";
            break;
        case 3:
            std::cout << "Задание №3\n";
            task3();
            std::cout << "-----\n";
            break;
        case 4:
            std::cout << "Задание №4\n";
            task4();
            std::cout << "-----\n";
            break;
        case 5:
            std::cout << "Задание №5\n";
            task5();
            std::cout << "-----\n";
            break;
        default:
            std::cout << "Номер задачи введен не верно либо не удалось конвертировать введенные данные\n";
            break;
        }
    }
}

void task1()
{
    const int BUFFER_SIZE = 255;
    char buffer[BUFFER_SIZE];

    std::cout << "Enter string: ";
    std::cin.getline(buffer, BUFFER_SIZE - 1);
    IntList1D invalidIdxs = checkBraces("()[]{}", buffer);

    if (!is_inited(invalidIdxs))
        std::cout << "Entered string is " << fgBrightGreen << "correct" << reset << "\n";
    else
    {
        std::cout << "Entered string is " << fgBrightRed << "invalid" << reset << ":\n";
        deleteList(invalidIdxs);
    }
    cinReset();
}

void task2()
{
}

void task3()
{
}

void task4()
{
    std::string path = printAndScan<std::string>("file path:");
    std::string pathOut = path + ".out";
    std::ifstream in(path);
}

void task5()
{
    std::string path = printAndScan<std::string>("file path:");
    std::string pathOut = path + ".out";
    std::ifstream in(path);
}