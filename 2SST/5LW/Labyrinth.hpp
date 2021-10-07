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
        for (unsigned i = 0; i < Lrows; ++i)
            labyrinth[i] = new char[Lcollumns];
    }

public:
    Labyrinth(const char *filename);
    ~Labyrinth();

    int shortestWay();
    void show();
};

#endif