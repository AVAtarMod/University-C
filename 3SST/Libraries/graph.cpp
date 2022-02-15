#include <cstring>
#include <sstream>

#include "graph.hpp"
#include "stack.hpp"

// SERVICE FUNCTIONS

bool allValuesTrue(bool* array, uint length);
bool validateMatrix(const matrix_t& matrix);
bool validateList(const List1D<List1D<int>> adjacencyList);
void printRowAL(const IntList1D rowOfAdjacencyList);
IntList1D* getSpanningTreeByDepth(const IntList1D* arrayOfLists, uint length);
IntList1D* getSpanningTreeByWidth(const IntList1D* arrayOfLists, uint length);
IntList1D* getArrayFrom(const List1D<List1D<int>> adjacencyList, uint size);
List1D<List1D<int>> getListOfListsFrom(const IntList1D* adjacencyArray,
                                       uint size);

Graph::Graph() {}

Graph::Graph(const matrix_t& adjacencyMatrix) {
    if (validateMatrix(adjacencyMatrix)) {
        size = adjacencyMatrix.size();
        adjacencyList = nullptr;

        for (uint row = 0; row < size; ++row) {
            List1D<int> listRow = nullptr;
            for (uint col = 0; col < size; ++col)
                for (int count = 0; count < adjacencyMatrix[row][col];
                     ++count) {
                    pushBack(listRow, static_cast<int>(col));
                }
            pushBack(adjacencyList, listRow);
        }
    }
}

Graph::Graph(const List1D<List1D<int>> adjacencyList) {
    List1D_element<List1D<int>>* list_ptr = *adjacencyList;
    while (list_ptr != nullptr) {
        pushBack(this->adjacencyList, copy(list_ptr->data));
        list_ptr = list_ptr->next;
    }
}

void Graph::operator=(const Graph& graph) {
    this->~Graph();
    size = graph.size;

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
    if (size != 0) {
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
    }
    return matrix;
}

Graph Graph::getSpanningTree(Method m) const {
    Graph spanningTree;
    spanningTree.size = size;
    const IntList1D* array = getArrayFrom(adjacencyList, size);
    List1D<List1D<int>>& resultList = spanningTree.adjacencyList;
    IntList1D* result;

    if (m == Method::BY_DEPTH) {
        result = getSpanningTreeByDepth(array, size);
    } else if (m == Method::BY_WIDTH) {
        result = getSpanningTreeByWidth(array, size);
    }
    resultList = getListOfListsFrom(result, size);
    for (uint i = 0; i < size; ++i) {
        deleteList(result[i]);
    }
    return spanningTree;
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
        delete[] buffer;
        buffer = nullptr;
        if (validateMatrix(matrix))
            graph = Graph(matrix);
    }
    if (buffer)
        delete[] buffer;
    return input;
}

void Graph::print() const {
    if (size != 0) {
        const List1D_element<List1D<int>>* list_ptr = *adjacencyList;
        for (uint i = 0; i < size && list_ptr; ++i) {
            std::cout << i + 1 << ": ";
            printRowAL(list_ptr->data);
            std::cout << '\n';
            list_ptr = list_ptr->next;
        }
    } else
        std::cout << "null";
}

bool Graph::validate() const { return validateList(adjacencyList); }

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

bool allValuesTrue(bool* array, uint length) {
    for (uint i = 0; i < length; ++i)
        if (array[i] == false)
            return false;

    return true;
}

bool validateMatrix(const matrix_t& matrix) {
    uint size = matrix.size();

    for (uint row = 0; row < size; ++row) {
        for (uint col = row; col < size; ++col)
            if (matrix[row][col] != matrix[col][row]) {
                std::string err =
                    "matrix data in (" + std::to_string(row) + ';' +
                    std::to_string(col) + ") doesn't match with (" +
                    std::to_string(col) + ';' + std::to_string(row) + ")";
                throw std::runtime_error(err);
                return false;
            }
    }
    return true;
}

// * Code not optimized
bool validateList(const List1D<List1D<int>> adjacencyList) {
    const List1D_element<List1D<int>>* list_ptr = *adjacencyList;
    int index = 0;
    while (list_ptr != nullptr) {
        const IntList1D row = list_ptr->data;
        const IntList1D_element* row_ptr = *row;

        while (row_ptr != nullptr) {
            int indexCheck = row_ptr->data;
            uint uIndexCheck = static_cast<uint>(indexCheck);

            if (indexCheck != index &&
                findFirstOf(getElementAt(adjacencyList, uIndexCheck)->data,
                            index) == -1)
                return false;
            row_ptr = row_ptr->next;
        }
        list_ptr = list_ptr->next;
        ++index;
    }
    return true;
}

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
    if (rowOfAdjacencyList)
        printRowALRecursion(*rowOfAdjacencyList, true);
}

IntList1D* getArrayFrom(const List1D<List1D<int>> adjacencyList, uint size) {
    IntList1D* result = new IntList1D[size]{nullptr};
    const List1D_element<List1D<int>>* list_ptr = *adjacencyList;
    for (uint i = 0; i < size && list_ptr; ++i) {
        result[i] = copy(list_ptr->data);
        list_ptr = list_ptr->next;
    }

    return result;
}

List1D<List1D<int>> getListOfListsFrom(const IntList1D* adjacencyArray,
                                       uint size) {
    List1D<List1D<int>> result = nullptr;

    for (uint i = 0; i < size; ++i) {
        pushBack(result, copy(adjacencyArray[i]));
    }

    return result;
}

int getNextIndexFromList(IntList1D list, const bool* isVertexViewed) {
    IntList1D_element* list_ptr = *list;
    int nextIndex = -1, index;
    while (list_ptr != nullptr && nextIndex == -1) {
        index = list_ptr->data;
        if (!isVertexViewed[index])
            nextIndex = index;
        list_ptr = list_ptr->next;
    }
    return nextIndex;
}

int getNextIndex(const bool* isVertexViewed, const IntList1D* arrayOfLists,
                 IntStack vertexes, int& index) {
    IntStack_element* currentData = nullptr;

    int nextIndexList =
        getNextIndexFromList(arrayOfLists[index], isVertexViewed);
    while (nextIndexList == -1) {
        currentData = pop(vertexes);
        if (currentData) {
            index = (currentData->data);
            nextIndexList =
                getNextIndexFromList(arrayOfLists[index], isVertexViewed);
            delete currentData;
        } else
            break;
    }
    return nextIndexList;
}

IntList1D* getSpanningTreeByDepth(const IntList1D* arrayOfLists, uint length) {
    IntList1D* result = new IntList1D[length];
    IntStack vertexes = nullptr;
    int index = 0, nextIndex = 0;

    bool* isVertexViewed = new bool[length]{false};
    do {
        push(vertexes, index);
        isVertexViewed[index] = true;
        nextIndex = getNextIndex(isVertexViewed, arrayOfLists, vertexes, index);
        if (nextIndex >= 0) {
            pushBack(result[nextIndex], index);
            pushBack(result[index], nextIndex);
        }
        index = nextIndex;
    } while (!allValuesTrue(isVertexViewed, length));
    delete[] isVertexViewed;
    deleteStack(vertexes);

    return result;
}

IntList1D* getSpanningTreeByWidth(const IntList1D* arrayOfLists, uint length) {
    IntList1D* result = new IntList1D[length];
    int index = 0, nextIndex = 0;
    IntStack vertexes = nullptr;

    bool* isVertexViewed = new bool[length]{false};
    do {
        push(vertexes, nextIndex);
        isVertexViewed[nextIndex] = true;
        nextIndex = getNextIndexFromList(arrayOfLists[index], isVertexViewed);
        if (nextIndex >= 0) {
            pushBack(result[nextIndex], index);
            pushBack(result[index], nextIndex);
        } else {
            nextIndex =
                getNextIndex(isVertexViewed, arrayOfLists, vertexes, index);
            if (nextIndex != -1 && index != -1) {
                pushBack(result[nextIndex], index);
                pushBack(result[index], nextIndex);
            }
        }

    } while (!allValuesTrue(isVertexViewed, length));
    delete[] isVertexViewed;
    deleteStack(vertexes);

    return result;
}
