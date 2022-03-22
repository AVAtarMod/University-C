#include "functions.hpp"

#include <fstream>
#include <sstream>

Graph::Graph(const char* filePath) {
    const int bufferSize = 255;
    std::ifstream input(filePath);

    if (!input.eof()) {
        input >> numberVertexes >> numberEdges;
        if (numberVertexes > 0)
            listOfEdges.resize(numberVertexes);
        else
            return;

        std::string line;
        std::stringstream stream;

        line.resize(bufferSize);
        int vertexIdx = 0;
        while (!input.eof()) {
            input.getline(line.data(), bufferSize);
            if (line[0] == '#')
                continue;
            int index = line.find(':');
            if (index != line.npos)
                line.erase(line.begin(), line.begin() + index);

            stream.str(line);

            int edgeIdx = 0;
            while (!stream.eof()) {
                stream >> listOfEdges[vertexIdx][edgeIdx];
                ++edgeIdx;
            }
            ++vertexIdx;
        }
        empty = false;
    }
}

bool Graph::isEmpty() const { return empty; }

std::vector<std::vector<int>> Graph::getListEdges() const {
    return listOfEdges;
}

int Graph::getNumberVertexes() const { return numberVertexes; }
int Graph::getNumberEdges() const { return numberEdges; }

bool isLinear(const Graph& g) {
    const int numberVertexes = g.getNumberVertexes(),
              numberEdges = g.getNumberEdges();
    bool condition1 = (numberEdges == numberEdges + 1);
    bool condition2;

    const std::vector<std::vector<int>>& list = g.getListEdges();

    condition1 = (list[0].size() == 1) && (list[0][0] == 1);
    for (uint i = 1; i < numberVertexes - 1; ++i) {
        bool is2Relation = (list[i].size() == 2);

        bool isLinear =
            is2Relation && (list[i][0] == i - 1) && (list[i][1] == i + 1);
        if (!is2Relation || !isLinear) {
            condition2 = false;
            break;
        }
    }
    condition1 = (list[numberVertexes - 1].size() == 1) &&
                 (list[numberVertexes - 1][0] == 1);

    if (condition1 && condition2)
        return true;
    else
        return false;
}

bool isHordalRing(const Graph& g) {}
bool isRingCycleShifting(const Graph& g) {}
bool isStar(const Graph& g) {}
bool isTree(const Graph& g) {}
bool isGrid(const Graph& g) {}
bool isFullGraph(const Graph& g) {}
bool isHyperSquare(const Graph& g) {}

Topology::Topology(Graph& graph) : g(graph) {}

std::vector<TopologyVariant> Topology::getTopology() { return variants; }

Topology::~Topology() {}
