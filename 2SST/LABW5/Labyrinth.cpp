#include "Labyrinth.hpp"
#include <vector>
#include <memory>
#include <algorithm>

#define isc static_cast<int>
#define lusc static_cast<long unsigned>

class Coordinate
{
public:
    int x, y, possibleWays = 0;
    bool lock;

    Coordinate()
    {
        x = 0, y = 0, lock = false;
    }
    Coordinate(int X, int Y, bool needLock = false)
    {
        x = X, y = Y, lock = needLock;
    }
    Coordinate(int *data, bool needLock = false)
    {
        x = data[0], y = data[1], lock = needLock;
    }

    friend bool operator==(const Coordinate &a, const Coordinate &b)
    {
        if (a.x == b.x && a.y == b.y) //TODO:need add impl && a.lock == b.lock
            return true;
        return false;
    }
    friend bool operator!=(const Coordinate &a, const Coordinate &b)
    {
        if (a.x == b.x && a.y == b.y) //TODO:need add impl && a.lock == b.lock
            return false;
        return true;
    }
};

void clearCoordinateData(Coordinate *array, unsigned from = 0, unsigned length = 1)
{
    for (size_t i = from; i < length; ++i)
    {
        array[i] = {0, 0, false};
    }
}

bool isEdge(Coordinate a, unsigned rows, unsigned collumns)
{
    if (a.x == -1 || a.y == -1 || a.x == isc(rows) || a.y == isc(collumns))
        return true;
    return false;
}

std::unique_ptr<Coordinate> returnOffset(Coordinate current, int i)
{
    std::unique_ptr<Coordinate> returnOffset;
    returnOffset.get()[0] = current;
    switch (i)
    {
    case 0:
        returnOffset->x = current.x + 1;
        return returnOffset;
        break;
    case 1:
        returnOffset->y = current.y + 1;
        return returnOffset;
        break;
    case 2:
        returnOffset->x = current.x - 1;
        return returnOffset;
        break;
    case 3:
        returnOffset->y = current.y - 1;
        return returnOffset;
        break;

    default:
        break;
    }
    return returnOffset;
}

int Labyrinth::shortestWay()
{
    Coordinate temp;
    int let = 0;
    Coordinate start = start;
    Coordinate finish = finish;
    if (start != finish)
    {
        char **bufferLabyrinth = new char *[this->Lrows];
        for (int i = 0; i < Lrows; ++i)
        {
            bufferLabyrinth[i] = new char[Lcollumns];
            for (int ii = 0; ii < Lcollumns; ++ii)
            {
                bufferLabyrinth[i][ii] = labyrinth[i][ii];
            }
        }

        const unsigned max_length_Labyrinth = (this->Lrows / 2 + 1) * this->Lcollumns + (this->Lrows / 2 + 1);
        std::vector<Coordinate> currentWay;
        currentWay.resize(max_length_Labyrinth);

        currentWay[0] = {this->start, false};
        std::vector<int> lengthsWays;

        bool isLastWayPassed = false;
        unsigned currentWayI = 0;
        while (!isLastWayPassed)
        {
            int cLength = 0;
            while (currentWay[currentWayI] != finish)
            {
                //TODO: may be need use bufferLabyrinth instead?
                std::vector<Coordinate> blacklist;
                //TODO: replace let -> ob.possibleWays
                int let = 0, cX = currentWay[currentWayI].x, cY = currentWay[currentWayI].y;
                bool itRepetitionPast = false;
                for (int i = 0; i < 4; ++i)
                {
                    temp = returnOffset(currentWay[currentWayI], i).get()[0];
                    if (isEdge(temp, Lrows, Lcollumns))
                    {
                        ++let;
                        break;
                    }
                    else if (bufferLabyrinth[temp.x][temp.y] == '1' || temp == currentWay[currentWayI])
                    {
                        ++let;
                        break;
                    }
                    else if (std::find(blacklist.begin(), blacklist.end(), temp) != blacklist.end())
                    {
                        ++let;
                        break;
                    }
                }
                temp.possibleWays = 4 - let;
                if (std::find(currentWay.begin(), currentWay.end(), temp) != currentWay.end())
                {
                    blacklist.push_back(currentWay[currentWayI]);
                    unsigned i = currentWayI;
                    while (temp.possibleWays < 2 && i != 0)
                    {
                        temp = currentWay[i];
                        --i;
                    }
                }
                if (temp.possibleWays == 0)
                    bufferLabyrinth[cX][cY] = '1';
                else
                {
                    ++currentWayI;
                    ++cLength;
                    currentWay[currentWayI] = temp;
                }
            }
            lengthsWays.push_back(cLength);
        }

        for (int i = 0; i < Lrows; ++i)
            delete[] bufferLabyrinth[i];
        delete[] bufferLabyrinth;

        return std::max_element(lengthsWays.begin(), lengthsWays.end())[0];
    }
    else
        return 0;
}