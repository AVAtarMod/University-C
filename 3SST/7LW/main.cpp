#include "B_Tree.hpp"

void task1();
void task2();

int main(int argc, char const* argv[])
{
    bool noData = false;
    if (argc == 1) {
        std::cout << "Select tree for operations: ";
        argc++;
        noData = true;
    }
    for (int i = 1; i < argc; i++) {
        int choice;
        if (noData) {
            std::cin >> choice;
            std::cin.ignore(32767, '\n');
        } else {
            choice = std::stoi(argv[i]);
        }

        switch (choice) {
        case 1:
            std::cout << "B-Tree\n";
            task1();
            std::cout << "-----\n";
            break;
        case 2:
            std::cout << "2-3-Tree\n";
            task2();
            std::cout << "-----\n";
            break;
        default:
            std::cerr << "Incorrect mode selected.\n";
            return 1;
        }
    }
}

void task1()
{
    bool exit = false;
    int parameter;
    int data;

    std::cout << "Enter parameter: ";
    std::cin >> parameter;
    std::cout << "\n";
    BTree btree(parameter);

    while (true) {
        int choice;
        std::cout << "1 - Print\n"
                  << "2 - Insert\n"
                  << "3 - Delete\n"
                  << "4 - Search\n"
                  << "5 - Exit\n"
                  << "Select operation: ";
        std::cin.ignore(32767, '\n');
        std::cin.clear();

        std::cin >> choice;

        switch (choice) {
        case 1:
            btree.print();
            std::cout << std::endl;
            break;
        case 2:
            std::cout << "Enter data:";
            std::cin >> data;
            btree.insert(data);
            break;
        case 3:
            std::cout << "Enter data:";
            std::cin >> data;
            btree.remove(data);
            break;
        case 4:
            std::cout << "Enter data:";
            std::cin >> data;
            btree.search(data);
            break;
        case 5:
            exit = true;
            break;

        default:
            std::cerr << "Incorrect mode selected.\n";
            break;
        }
        if (exit)
            break;
    }
}
void task2()
{
    BTree btree(2);
    int data = 0;
    bool exit;

    while (true) {
        int choice;
        std::cout << "1 - Print\n"
                  << "2 - Insert\n"
                  << "3 - Delete\n"
                  << "4 - Search\n"
                  << "5 - Exit\n"
                  << "Select operation: ";
        std::cin.ignore(32767, '\n');
        std::cin.clear();

        std::cin >> choice;

        switch (choice) {
        case 1:
            btree.print();
            std::cout << std::endl;
            break;
        case 2:
            std::cout << "Enter data:";
            std::cin >> data;
            btree.insert(data);
            break;
        case 3:
            std::cout << "Enter data:";
            std::cin >> data;
            btree.remove(data);
            break;
        case 4:
            std::cout << "Enter data:";
            std::cin >> data;
            if (btree.search(data))
                std::cout << "Found";
            else
                std::cout << "Not found";
            break;
        case 5:
            exit = true;
            break;

        default:
            std::cerr << "Incorrect mode selected.\n";
            break;
        }
        if (exit)
            break;
    }
}
