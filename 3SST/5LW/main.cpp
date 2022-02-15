#include <fstream>
#include <iostream>

#include "graph.hpp"
#include "useful.hpp"

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();

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
            std::cout << "Номер задачи введён не верно либо не удалось "
                         "конвертировать введённые данные\n";
            break;
        }
    }
}

void task1() {
    std::string filePath = printAndScan<std::string>("Enter path:");
    std::ifstream in(filePath);
    if (!in.eof()) {
        Graph graph;
        try {
            in >> graph;
            graph.print();

            std::cout << "\nConverted to matrix:\n";
            matrix_t matrix = graph.getAdjacencyMatrix();
            for (auto& row : matrix) {
                for (auto& element : row) {
                    std::cout << element << " ";
                }
                std::cout << '\n';
            }
            std::cout << "\nSpanning Tree (by depth):\n";
            Graph spanTree = graph.getSpanningTree(Graph::Method::BY_DEPTH);
            spanTree.print();
            std::cout << "\nSpanning Tree (by width):\n";
            spanTree = graph.getSpanningTree(Graph::Method::BY_WIDTH);
            spanTree.print();
        }
        catch (const std::exception& e) {
            std::cerr << "\nERROR:" << e.what() << '\n';
        }

    } else
        std::cerr << "Error: Cannot open file.";
}

void task2() {}
void task3() {}
void task4() {}
void task5() {}
void task6() {}
void task7() {}
