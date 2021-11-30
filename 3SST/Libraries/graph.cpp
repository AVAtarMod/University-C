#include <cstring>
#include <sstream>

#include "graph.hpp"

// SERVICE FUNCTIONS

void printRowAL(const IntList1D rowOfAdjacencyList);

Graph::Graph() {}

Graph::Graph(const matrix_t& adjacencyMatrix) {
    size = adjacencyMatrix.size();
    adjacencyList = nullptr;

    for (uint row = 0; row < size; ++row) {
        List1D<int> listRow = nullptr;
        for (uint col = 0; col < size; ++col)
            for (int count = 0; count < adjacencyMatrix[row][col]; ++count) {
                pushBack(listRow, static_cast<int>(col));
            }
        pushBack(adjacencyList, listRow);
    }
}

Graph::Graph(const List1D<List1D<int>> adjacencyList) {}

void Graph::operator=(const Graph& graph) {
    this->~Graph();
    this->size = graph.size;

    adjacencyList = nullptr;
    List1D_element<List1D<int>>* list_ptr = *graph.adjacencyList;
    for (uint i = 0; i < size; ++i) {
        pushBack(adjacencyList, copy(list_ptr->data));
        list_ptr = list_ptr->next;
    }
}

List1D<List1D<int>> Graph::getAdjacencyList() const {
    if (size == 0)
        return nullptr;

    List1D<List1D<int>> result = nullptr;
    List1D_element<List1D<int>>* list_ptr = *adjacencyList;
    for (uint i = 0; i < size; ++i) {
        pushBack(result, copy(list_ptr->data));
        list_ptr = list_ptr->next;
    }
    return result;
}

const matrix_t Graph::getAdjacencyMatrix() const {
    matrix_t matrix(size, std::vector<int>(size, 0));
    List1D_element<List1D<int>>* list_ptr = *adjacencyList;
    for (uint row = 0; row < size; ++row) {
        IntList1D_element* vertexIndex_ptr = *(list_ptr->data);
        for (uint col = 0; col < size; ++col) {
            while (vertexIndex_ptr &&
                   col == static_cast<uint>(vertexIndex_ptr->data)) {
                ++matrix[col][row];
                vertexIndex_ptr = vertexIndex_ptr->next;
            }
        }
        list_ptr = list_ptr->next;
    }
    return matrix;
}

IntTree Graph::getSpanningTree(Method m) const {
    if (m == Method::BY_DEPTH) {

    } else if (m == Method::BY_WIDTH) {
    }
    
    return IntTree();
}

std::istream& operator>>(std::istream& input, Graph& graph) {
    char* buffer = new char[INT8_MAX];
    input.getline(buffer, INT8_MAX, '\n');

    if (!input.eof() && strlen(buffer) != 0) {
        const int maxPossibleSize = INT8_MAX / 2 + 1;
        matrix_t matrix(1, std::vector<int>(maxPossibleSize));
        std::stringstream stream(buffer);

        uint matrixSize = 0;
        for (uint col = 0; !stream.eof(); ++col) {
            stream >> matrix[0][col];
            ++matrixSize;
        }

        matrix.resize(matrixSize);
        for (auto& i : matrix) {
            i.resize(matrixSize);
        }

        for (uint row = 1; row < matrixSize; ++row) {
            for (uint col = 0; col < matrixSize; ++col) {
                input >> matrix[row][col];
            }
        }
        graph = Graph(matrix);
    }
    delete[] buffer;
    return input;
}

void Graph::print() const {
    if (size != 0) {
        const List1D_element<List1D<int>>* list_ptr = *adjacencyList;
        for (uint i = 0; i < size; ++i) {
            std::cout << i + 1 << ": ";
            printRowAL(list_ptr->data);
            std::cout << '\n';
            list_ptr = list_ptr->next;
        }
    } else
        std::cout << "null";
}

Graph::~Graph() {
    if (size != 0) {
        List1D_element<List1D<int>>* list_ptr = *adjacencyList;

        for (uint i = 0; i < size; ++i) {
            deleteList(list_ptr->data);
            list_ptr = list_ptr->next;
        }
        deleteList(adjacencyList);
        size = 0;
    }
}

// SERVICE FUNCTIONS

void printRowALRecursion(const IntList1D_element* begin, bool start) {
    if (begin != nullptr) {
        if (start)
            std::cout << begin->data + 1;
        else
            std::cout << " " << begin->data + 1;
        printRowALRecursion(begin->next, false);
    }
}

void printRowAL(const List1D<int> rowOfAdjacencyList) {
    printRowALRecursion(*rowOfAdjacencyList, true);
}
