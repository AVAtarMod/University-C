#include "Labyrinth.hpp"
#include <vector>
#include <memory>
#include <algorithm>

#define isc static_cast<int>
#define lusc static_cast<long unsigned>

Labyrinth::Labyrinth(const char *filename)
{
    if (isFileExist(filename))
    {
        std::ifstream fileWithLabyrinth(filename);
        std::string buffer;

        fileWithLabyrinth >> buffer;
        if (buffer.find_first_of("#") == buffer.npos)
            this->Lrows = std::stoul(buffer.data());
        if (this->Lrows < 1)
            std::cerr << "Unable read number of rows!\n";

        fileWithLabyrinth >> buffer;
        if (buffer.find_first_of("#") == buffer.npos)
            this->Lcollumns = std::stoul(buffer.data());
        if (this->Lcollumns < 1)
            std::cerr << "Unable read number of rows!\n";

        buffer.reserve(UINT8_MAX);
        fileWithLabyrinth.getline(buffer.data(), UINT8_MAX, '\n');
        for (unsigned i = 0; i < 2; ++i)
        {
            fileWithLabyrinth >> buffer;
            start[i] = std::stoul(buffer.data());
        }

        fileWithLabyrinth.getline(buffer.data(), UINT8_MAX, '\n');
        for (unsigned i = 0; i < 2; ++i)
        {
            fileWithLabyrinth >> buffer;
            finish[i] = std::stoul(buffer.data());
        }

        bool startL = false;
        char *cBuffer = new char[UINT8_MAX + 1];
        unsigned pos;
        while (!startL)
        {
            startL = true;
            pos = fileWithLabyrinth.tellg();
            fileWithLabyrinth.getline(cBuffer, UINT8_MAX, '\n');
            buffer = cBuffer;

            if ((buffer.find('1') == buffer.npos || buffer.find('0') == buffer.npos) && buffer.find(' ') == buffer.npos)
                startL = false;
            for (unsigned bufI = 0; bufI < buffer.size() && startL; ++bufI)
            {
                char i = buffer[bufI];
                if (i != ' ' && i != 'a' && i != '0' && i != '1' && i != 'b')
                    startL = false;
            }
        }
        fileWithLabyrinth.seekg(pos);
        delete[] cBuffer;
        cBuffer = nullptr;

        this->labyrinth = new char *[this->Lrows];
        init(this->labyrinth);

        labyrinth[0][0] = buffer.data()[0];
        for (unsigned i = 0; i < this->Lrows; ++i)
            for (unsigned ii = 0; ii < this->Lcollumns; ++ii)
            {
                fileWithLabyrinth >> buffer;
                labyrinth[i][ii] = buffer.data()[0];
            }
    }
}

Labyrinth::~Labyrinth()
{
    for (unsigned i = 0; i < Lrows; ++i)
        delete[] labyrinth[i];
    delete[] labyrinth;
}

void Labyrinth::show()
{
    std::cout << "Rows = " << Lrows << "; Collumns = " << Lcollumns << "\n";
    for (unsigned i = 0; i < Lrows; ++i)
    {
        for (unsigned ii = 0; ii < Lcollumns; ++ii)
        {
            std::cout << labyrinth[i][ii] << " ";
        }
        std::cout << "\n";
    }
}

bool isFileExist(const char *file)
{
    bool exist = false;

    std::ifstream in(file);
    if (in.good())
    {
        exist = true;
    }
    in.close();

    return exist;
}

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

bool isEdge(Coordinate a, unsigned rows, unsigned collumns)
{
    if (a.x == -1 || a.y == -1 || a.x == isc(rows) || a.y == isc(collumns))
        return true;
    return false;
}

std::unique_ptr<Coordinate> returnOffset(Coordinate current, int i)
{
    std::unique_ptr<Coordinate> returnOffset_ptr(new Coordinate(0, 0, false));
    *returnOffset_ptr = current;
    switch (i)
    {
    case 0:
        returnOffset_ptr->x = current.x + 1;
        return returnOffset_ptr;
        break;
    case 1:
        returnOffset_ptr->y = current.y + 1;
        return returnOffset_ptr;
        break;
    case 2:
        returnOffset_ptr->x = current.x - 1;
        return returnOffset_ptr;
        break;
    case 3:
        returnOffset_ptr->y = current.y - 1;
        return returnOffset_ptr;
        break;

    default:
        break;
    }

    return returnOffset_ptr;
}

int Labyrinth::shortestWay()
{
    Coordinate start = this->start;
    Coordinate finish = this->finish;
    if (start != finish)
    {
        /**
         * @brief Making 'shadow' copy
         */
        char **bufferLabyrinth = new char *[this->Lrows];
        for (unsigned i = 0; i < Lrows; ++i)
        {
            bufferLabyrinth[i] = new char[Lcollumns];
            for (unsigned ii = 0; ii < Lcollumns; ++ii)
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
        Coordinate temp;
        while (!isLastWayPassed)
        {
            int cLength = 0;
            while (currentWay[currentWayI] != finish)
            {
                //TODO: replace let -> ob.possibleWays
                int let = 0, cX = currentWay[currentWayI].x, cY = currentWay[currentWayI].y;
                // bool itRepetitionPast = false;
                for (int i = 0, hardLet = 0; i < 4; ++i)
                {
                    Coordinate tempCurrent = returnOffset(currentWay[currentWayI], i).get()[0];
                    bool goodCoordinate = true;
                    if (isEdge(tempCurrent, Lrows, Lcollumns))
                    {
                        ++let, ++hardLet;
                        goodCoordinate = false;
                    }

                    else if (bufferLabyrinth[tempCurrent.x][tempCurrent.y] == '1')
                    {
                        ++let, ++hardLet;
                        goodCoordinate = false;
                    }
                    else if (tempCurrent == currentWay[currentWayI])
                    {
                        ++let;
                        goodCoordinate = false;
                    }
                    else if (std::find(currentWay.begin(), currentWay.end(), tempCurrent) != currentWay.end())
                    {
                        ++let;
                        goodCoordinate = false;
                    }
                    if (goodCoordinate)
                        temp = tempCurrent;
                    if (hardLet == 3)
                        bufferLabyrinth[cX][cY] = '1';
                }
                temp.possibleWays = 4 - let;

                /**
                 * @brief Pass way from end to begin; find first
                 * good coordinate
                 */
                if (temp.possibleWays == 0)
                {
                    if (bufferLabyrinth[cX][cY] != '1')
                    {
                        int i = currentWayI;
                        while (currentWay.at(i).possibleWays - 1 <= 0 && i >= 0)
                            --i;
                        bufferLabyrinth[currentWay[i+1].x][currentWay[i+1].y] = '1';
                        currentWay.resize(i + 1);
                    }
                }
                else
                {
                    ++currentWayI;
                    ++cLength;
                    currentWay[currentWayI] = temp;
                }
            }
            lengthsWays.push_back(cLength);
        }

        for (unsigned i = 0; i < Lrows; ++i)
            delete[] bufferLabyrinth[i];
        delete[] bufferLabyrinth;

        return std::min_element(lengthsWays.begin(), lengthsWays.end())[0];
    }
    else
        return 0;
}