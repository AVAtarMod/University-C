// Вариант №1
#include <iostream>

#include "list.hpp"
#include "useful.hpp"

void task1();
void task2();
void task3();

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

        switch (choice) {
        case 1:
            std::cout << "Задание №1\n";
            task1();
            std::cout << "-----\n";
            break;
        case 2:
            std::cout << "Задание №1\n";
            task2();
            std::cout << "-----\n";
            break;
        case 3:
            std::cout << "Задание №1\n";
            task3();
            std::cout << "-----\n";
            break;
        default:
            std::cout << "Номер задачи введён не верно либо не удалось "
                         "конвертировать введённые данные\n";
            break;
        }
    }
}

void task1() {
    IntList1D list = readArrayKeyboard();
    IntList1D_element* list_ptr = (list) ? *list : nullptr;

    uint lengthSequence = 0;
    if (list_ptr != nullptr) {
        ++lengthSequence;
        do {
            int prevData = list_ptr->data;
            list_ptr = list_ptr->next;

            if (list_ptr->data <= prevData)
                ++lengthSequence;

            prevData = list_ptr->data;
        } while (list_ptr->next != nullptr);
    }
    std::cout << "Length of sequence: " << lengthSequence << "\n";
}

void task2() {
    IntList1D list = readArrayKeyboard();

    const int length = static_cast<int>(getLength(list));
    IntList1D indexes = nullptr;
    for (int i = 0; i < length; ++i)
        if ((i + 1) % 2 == 0)
            pushBack(indexes, i);

    IntList1D deleted = popByIndexes(list, indexes);
    deleteList(deleted);
    deleteList(indexes);

    indexes = getIndexesByComparator(list, comparator::negative);
    doActionOnIndexes(list, indexes, index_actions::pushBefore, 0);
    printBegin(list);
    std::cout << "\n";
}

void task3() {
    IntList1D list = readArrayKeyboard();
    IntList1D_element* const list_ptr = (list) ? *list : nullptr;

    bool sorted = false;
    while (!sorted) {
        IntList1D_element* tmp = list_ptr;

        sorted = true;
        while (tmp != nullptr) {
            if (tmp->next) {
                if (tmp->data > tmp->next->data) {
                    sorted = false;

                    int tmp_data = tmp->data;
                    tmp->data = tmp->next->data;
                    tmp->next->data = tmp_data;
                }
            }
            tmp = tmp->next;
        }
    }
    printBegin(list);
    std::cout << "\n";
}
