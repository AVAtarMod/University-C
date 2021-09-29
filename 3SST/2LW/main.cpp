#include <iostream>
#include <sstream>

#include "list.hpp"

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();

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
        case 6:
            std::cout << "Задание №6\n";
            task6();
            std::cout << "-----\n";
            break;
        case 7:
            std::cout << "Задание №7\n";
            task7();
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
    intList1D list1 = nullptr;
    intList1D list2 = nullptr;
    int userInput;
    while (true)
    {
        std::cin >> userInput;
        if (std::cin.eof())
            break;
        insertUpperSorted(list1, userInput, USE_RECURSION);
        insertUpperSorted(list2, userInput, USE_CYCLE);
    }
    std::cout << "Recursion: ";
    printBegin(list1);
    std::cout << "\nCycle: ";
    printBegin(list2);
    std::cout << "\n";

    deleteList(list1);
    deleteList(list2);
    std::cin.clear();
}

void task2()
{
    const int BUFFSIZE = 255;
    intList1D list1 = nullptr;
    intList1D list2 = nullptr;
    int userInput;
    std::cout << "[INFO] Entered data must be lesser than " << BUFFSIZE + 1 << "\n";
    std::cout << "Enter list #1:\n";
    std::stringstream stream;

    char buffer[BUFFSIZE];
    std::cin.getline(buffer, BUFFSIZE);
    stream.str(buffer);
    while (!stream.eof())
    {
        stream >> userInput;
        insertUpperSorted(list1, userInput, USE_CYCLE);
    }

    std::cout << "\nEnter list #2:\n";
    std::cin.getline(buffer, BUFFSIZE);

    stream.clear();
    stream.str(buffer);

    while (!stream.eof())
    {
        stream >> userInput;
        insertUpperSorted(list2, userInput, USE_CYCLE);
    }

    intList1D merged = mergeUpperSorted(list1, list2);
    std::cout << "\nMerged list: ";
    printBegin(merged);
    deleteList(list1);
    deleteList(list2);
    deleteList(merged);
    std::cout << "\n";
}

void task3()
{
    intList1D userInput = readArrayKeyboard(IO_EOF);
    intList1D reversed = reverse(userInput);
    intList1D positive = filter(userInput, comparator::positive);
    intList1D negative_reversed = filter(reversed, comparator::negative);

    std::cout << "List of positive numbers: ";
    if (positive != nullptr)
        printBegin(positive);
    else
        std::cout << "null";

    std::cout << "\nReversed list of negative numbers: ";
    if (negative_reversed != nullptr)
        printBegin(negative_reversed);
    else
        std::cout << "null";

    deleteList(userInput);
    deleteList(reversed);
    deleteList(positive);
    deleteList(negative_reversed);
    std::cout << "\n";
}

void task4()
{
    std::string path = printAndScan<std::string>("file path:");
    std::list<intList1D> arLists = fileToLists(path, '|');
    if (arLists.size() >= 2)
    {
        intList1D listA = *(arLists.begin());
        arLists.pop_front();
        intList1D listB = *(arLists.begin());
        intList1D merged = mergeByAction(listA, listB, merge_actions::sum);

        std::cout << "\nList merged by action: ";
        printBegin(merged);
        deleteList(merged);
        deleteList(listA);
        deleteList(listB);
        std::cout << "\n";
    }
}

void task5()
{
    intList1D list1 = readArrayKeyboard(NEWLINE, 255, true);
    intList1D list2 = readArrayKeyboard(NEWLINE);
    int numberSearch = printAndScan<int>("\nEnter number for search: ");

    int indexOfCut = findFirstOf(list1, numberSearch) + 1;
    intList1D sublist = cutByIndexRange(list1, indexOfCut, 0);

    /**
     * @brief Construct a new list by appending sublist before list2
     * (link method)
     */
    appendFront(list2, sublist);

    std::cout << "\nResult list: ";
    printBegin(list2);

    /**
     * @brief Now we delete list2+sublist, 
     * therefore we not need to delete sublist
     */
    deleteList(list2);

    deleteList(list1);
    std::cout << "\n";
}

void task6()
{
    intList1D list = readArrayKeyboard(NEWLINE, 255, true);
    int numberSearch = printAndScan<int>("\nEnter number for search: ");

    int indexOfZero = findFirstOf(list, 0);
    intList1D indexes = getIndexesByData(list, numberSearch);
    if (indexOfZero == -1)
        indexOfZero = 0;
    else
    {
        intList1D filtered_indexes = filter(indexes, comparator::lesserThanData, indexOfZero);
        deleteList(indexes);
        *indexes = *filtered_indexes;
    }

    doActionOnIndexes(list, indexes, index_actions::deleteElement);
    std::cout << "\nResult list: ";
    printBegin(list);

    deleteList(list);
    deleteList(indexes);
    std::cout << "\n";
}

void task7()
{
}
