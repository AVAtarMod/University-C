#include <iostream>
#include <fstream>
#include <iomanip>

#include "stack.hpp"
#include "queue.hpp"
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
    bool strIsValid = checkBraces("()[]{}", buffer);

    if (strIsValid)
        std::cout << "Entered string is " << fgBrightGreen << "correct" << reset;
    else
    {
        std::cout << "Entered string is " << fgBrightRed << "invalid" << reset;
    }
    cinReset();
}

void task2()
{
    const int BUFFER_SIZE = 255;
    const int type =
        printAndScan<int>("Supported types RPN expressions:\n"
                          "1) char\n"
                          "2) positive numbers\n"
                          "3) negative numbers\n"
                          "4) float numbers\n\n"
                          "Enter type: ");
    char buffer[BUFFER_SIZE];

    std::cout << "Enter expression: ";
    std::cin.getline(buffer, BUFFER_SIZE - 1);

    try
    {
        if (1 <= type && type <= 2)
            std::cout << "Result: " << evalRpnExpression<int>(buffer);
        else if (type == 3)
            std::cout << "Result: " << evalRpnExpression<long>(buffer);
        else if (type == 4)
            std::cout << std::setprecision(8) << "Result: " << evalRpnExpression<float>(buffer);
    }
    catch (const std::exception &ex)
    {
        std::cerr << fgBrightRed << "Error: " << reset << ex.what() << '\n';
    }

    cinReset();
}

void task3()
{
    const int BUFFER_SIZE = 255;
    char buffer[BUFFER_SIZE];

    std::cout << "Enter expression: ";
    std::cin.getline(buffer, BUFFER_SIZE - 1);
    const int type =
        printAndScan<int>("Supported types RPN expressions:\n"
                          "1) char\n"
                          "2) positive numbers\n"
                          "3) negative numbers\n"
                          "4) float numbers\n\n"
                          "Enter type: ");
    try
    {
        /**
         * Examples:
         * 1a) 25 + ( 3 * 4 ^ ( 3 + 2 ) ) * 4
         * 1b) 2.5 3 4 3 2 + ^ * 4 * +
         * 
         * 2a) 2.5 + 5 * 4 - 3
         * 2b) 2.5 5 * 4 + 3 -
         * 
         * 3a) 2 + 5 * 3 - 10
         * 3b) 2 5 3 * 10 - +
         */
        std::string rpnExpression = convertToRpnExpression(buffer);
        std::cout << "RPN Expression: "
                  << rpnExpression
                  << "\n";
        std::string resultEval;
        if (1 <= type && type <= 2)
            resultEval = std::to_string(evalRpnExpression<int>(rpnExpression));
        else if (type == 3)
            resultEval = std::to_string(evalRpnExpression<long>(rpnExpression));
        else if (type == 4)
            resultEval = std::to_string(evalRpnExpression<float>(rpnExpression));
        std::cout << std::setprecision(8) << "Result of evaluating RPN expression: " << resultEval;
    }
    catch (const std::exception &ex)
    {
        std::cerr << fgBrightRed << "Error: " << reset << ex.what() << '\n';
    }
    cinReset();
}

void task4()
{
    std::string path = printAndScan<std::string>("file path: ");
    std::string pathOut = path + ".out";
    std::ifstream in(path);
    int range[2];
    range[0] = printAndScan<int>("Enter A: ");
    range[1] = printAndScan<int>("Enter B: ");

    IntQueue queue;

    IntList1D_element *lastIndex = nullptr;
    IntList1D lastIndexList = &lastIndex;

    int number;
    in >> number;
    bool endPushed = false;
    while (!in.eof())
    {
        if (number < range[0])
        {
            pushFront(queue.list, number);
            if (endPushed)
                (*lastIndexList)->data += 1;
        }
        else if (number <= range[1])
        {
            if (endPushed)
            {
                doActionOnIndexes(queue.list, lastIndexList, index_actions::pushBefore, number);
                (*lastIndexList)->data += 1;
            }
            else
                pushBack(queue.list, number);
        }
        else
        {
            pushBack(queue.list, number);
            if (!endPushed)
                *lastIndexList = new IntList1D_element(static_cast<int>(getLength(queue.list) - 1));
            endPushed = true;
        }

        in >> number;
        updateFields(queue);
    }
    delete *lastIndexList;

    in.close();
    std::ofstream out(pathOut);
    while (!isEmpty(queue))
    {
        IntQueue_element *tmp = popFront(queue.list);
        out << tmp->data << " ";
        delete tmp;
        updateFields(queue);
    }

    out.close();
    deleteQueue(queue);
}

void task5()
{
    std::string path = printAndScan<std::string>("file path: ");

    std::ifstream in(path);
    std::ofstream out(path + ".out");
    IntQueue queue;

    std::string buffer;

    while (!in.eof())
    {
        buffer.resize(UINT8_MAX);
        in.getline(buffer.data(), UINT8_MAX);
        buffer.resize(buffer.find('\0'));
        for (uint i = 0; i < buffer.size(); ++i)
        {
            char current = buffer[i];
            if (isdigit(current))
                push(queue, current - '0');
            else
                out << current;
        }
        out << " ";
        while (!isEmpty(queue))
        {
            IntQueue_element *tmp = pop(queue);
            out << tmp->data;
            delete tmp;
        }
        out << "\n";
    }
}
