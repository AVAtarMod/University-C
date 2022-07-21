#ifndef FUNCTIONS_LIB
#define FUNCTIONS_LIB

#include <vector>

class Graph {
private:
    bool empty = true;
    std::vector<std::vector<int>> listOfEdges;
    int numberVertexes = 0, numberEdges = 0;

public:
    Graph(const char* filePath);

    bool isEmpty() const;

    std::vector<std::vector<int>> getListEdges() const;
    int getNumberVertexes() const;
    int getNumberEdges() const;

    ~Graph();
};

enum class TopologyVariant {
    Linear,
    Ring,
    HordalRing,
    RingCycleShifting,
    Star,
    Tree,
    Grid,
    FullGraph,
    HyperSquare
};

class Topology {
private:
    Graph& g;
    std::vector<TopologyVariant> variants;

public:
    Topology(Graph& graph);
    std::vector<TopologyVariant> getTopology();
    ~Topology();
};
#endif // FUNCTIONS_LIB
