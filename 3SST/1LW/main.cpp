#include <iostream>

#include "useful.hpp"
#include "functions.hpp"

void task5();
void task6();
void task7();
void task8();

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
        case 5:
            std::cout << "Задание №5\n";
            task5();
            break;
        case 6:
            std::cout << "Задание №6\n";
            task6();
            break;
        case 7:
            std::cout << "Задание №7\n";
            task7();
            break;
        case 8:
            std::cout << "Задание №7\n";
            task8();
            break;
        default:
            std::cout << "Номер задачи введен не верно либо не удалось конвертировать введенные данные\n";
            break;
        }
    }
}

void task5()
{
    const int LENGTH = 4;
    intList2D_element *begin = new intList2D_element(nullptr, getRandomNumber(-100, 100)), *temp = begin, *prev;

    for (int currentLength = 1; currentLength < LENGTH; ++currentLength)
    {
        prev = temp;

        temp->next = new intList2D_element;
        temp = temp->next;
        temp->previous = prev;
        temp->data = getRandomNumber(-100, 100);
    }

    std::cout << "sum:" << sumChain(begin) << "\nfrom begin: ";
    printFromBegin(begin);
    std::cout << "\nfrom end: ";
    printFromEnd(temp);
    std::cout << "\n-------\n";
    del(begin);
}

void task6()
{
    std::string path = printAndScan<std::string>("file path:");
    std::list<int> numbers = readArrayFile(path);
    const int num_size = numbers.size();
    intList2D_element *begin = new intList2D_element(nullptr, *numbers.cbegin());
    intList2D_element *prev = nullptr, *temp = begin;
    for (uint16_t i = 0; i < num_size - 1; ++i)
    {
        prev = temp;
        numbers.pop_front();

        temp->next = new intList2D_element;
        temp = temp->next;
        temp->previous = prev;
        temp->data = *numbers.cbegin();
    }

    std::cout << greaterThenIndex(begin, 0) << "\n-------\n";
    del(begin);
}

void task7()
{
    std::list<int> numbers = readArrayKeyboard(ZERO);
    const int num_size = numbers.size();
    intList2D_element *begin = new intList2D_element(nullptr, *numbers.cbegin());
    intList2D_element *prev = nullptr, *temp = begin;
    for (uint16_t i = 0; i < num_size - 1; ++i)
    {
        prev = temp;
        numbers.pop_front();

        temp->next = new intList2D_element;
        temp = temp->next;
        temp->previous = prev;
        temp->data = *numbers.cbegin();
    }

    std::cout << sumChain(begin) * 1.0 / num_size << "\n-------\n";
    del(begin);
}

void task8()
{
    std::list<int> numbers = readArrayKeyboard(IO_EOF);
    const int num_size = numbers.size();
    intList2D_element *begin = new intList2D_element(nullptr, *numbers.cbegin());
    intList2D_element *prev = nullptr, *temp = begin;
    for (uint16_t i = 0; i < num_size - 1; ++i)
    {
        prev = temp;
        numbers.pop_front();

        temp->next = new intList2D_element;
        temp = temp->next;
        temp->previous = prev;
        temp->data = *numbers.cbegin();
    }

    std::cout << maxElementData(begin) << "\n-------\n";
    del(begin);
}
