#ifndef GRAPH_LIB
#define GRAPH_LIB

#include <vector>

#include "list.hpp"
#include "tree.hpp"

using matrix_t = std::vector<std::vector<int>>;

class Graph {
  private:
    uint size = 0;
    List1D<List1D<int>> adjacencyList = nullptr;

  public:
    enum Method { BY_DEPTH, BY_WIDTH };

    Graph();
    Graph(const matrix_t& adjacencyMatrix);
    Graph(const List1D<List1D<int>> adjacencyList);

    void operator=(const Graph& graph);

    List1D<List1D<int>> getAdjacencyList() const;
    const matrix_t getAdjacencyMatrix() const;
    IntTree getSpanningTree(Method m) const;
    void print() const;
    void validate() const;

    friend std::istream& operator>>(std::istream& input, Graph& number);

    ~Graph();
};

std::istream& operator>>(std::istream& input, Graph& number);

#endif // GRAPH_LIB
