#include <fstream>
#include <iomanip>
#include <iostream>

// TODO: fix include
#include "longNumbers.hpp"

void task1();
void task2();
void task3();
void task4();

int main(int argc, char const* argv[]) {
    bool noData = false;
    if (argc == 1) {
        printf("Введите программу для запуска: ");
        argc++;
        noData = true;
    }
    for (int i = 1; i < argc; i++) {
        int choice;
        if (noData) {
            scanf("%d", &choice);
            std::cin.ignore(32767, '\n');
        } else {
            choice = std::stoi(argv[i]);
        }

        try {
            switch (choice) {
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
            default:
                std::cout << "Номер задачи введен не верно либо не удалось "
                             "конвертировать введенные данные\n";
                break;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "\nERROR: " << e.what() << '\n';
        }
    }
}

void task1() {
    int number;
    std::cout << "Enter number for computing factorial: ";
    std::cin >> number;
    std::cout << fact(number) << "\n";
}

void task2() {
    LongNumber A, B;
    std::cout << "Enter number A: ";
    std::cin >> A;
    std::cout << "Enter number B: ";
    std::cin >> B;
    std::cout << "Result: A*B = " << A * B << "\n";
}

void task3() {
    LongNumber A, B;
    std::cout << "Enter number A: ";
    std::cin >> A;
    std::cout << "Enter number B: ";
    std::cin >> B;

    LongNumber result;
    std::string greatest;
    if (A > B) {
        greatest = "A";
        result = A - B;
    } else {
        greatest = "B";
        result = B - A;
    }

    std::cout << "Greatest number is " << greatest << "\n";
    std::cout << "Result: MAX-MIN = " << result << "\n";
}
void task4() {
    LongNumber A, B;
    std::cout << "Enter number A: ";
    std::cin >> A;
    std::cout << "Enter number B: ";
    std::cin >> B;
    std::cout << "Result: A/B = " << A / B << "\n";
}
