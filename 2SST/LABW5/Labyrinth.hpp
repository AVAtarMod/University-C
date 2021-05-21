#ifndef LABYRINTH
#define LABYRINTH

bool isFileExist(const char *file);

#include <fstream>
#include <string>
#include <iostream>

class Labyrinth
{
private:
    unsigned Lrows, Lcollumns;
    char **labyrinth;
    int start[2], finish[2];
    void init(char **labyrinth)
    {
        for (int i = 0; i < Lrows; ++i)
            labyrinth[i] = new char[Lcollumns];
    }

public:
    Labyrinth(const char *filename);
    ~Labyrinth();

    int shortestWay();
};

Labyrinth::Labyrinth(const char *filename)
{
    if (isFileExist(filename))
    {
        std::ifstream fileWithLabyrinth(filename);
        std::string buffer = "#";
        while (buffer.find_first_of("#") != buffer.npos)
            fileWithLabyrinth >> buffer;
        this->Lrows = atoi(buffer.data());

        if (this->Lrows < 1)
            std::cerr << "Unable read number of rows!\n";

        while (buffer.find_first_of("#") != buffer.npos)
            fileWithLabyrinth >> buffer;
        this->Lcollumns = atoi(buffer.data());

        if (this->Lcollumns < 1)
            std::cerr << "Unable read number of collumns!\n";

        while (buffer.size() != 1 && !isdigit(buffer.data()[0]))
            fileWithLabyrinth >> buffer;

        this->labyrinth = new char *[this->Lrows];
        init(this->labyrinth);

        labyrinth[0][0] = buffer.data()[0];
        for (int i = 0; i < this->Lrows; ++i)
            for (int ii = 0; ii < this->Lcollumns; ++ii)
            {
                fileWithLabyrinth >> buffer;
                labyrinth[i][ii] = buffer.data()[0];
            }
    }
}

Labyrinth::~Labyrinth()
{
    for (int i = 0; i < Lrows; ++i)
        delete[] labyrinth[i];
    delete[] labyrinth;
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

#endif