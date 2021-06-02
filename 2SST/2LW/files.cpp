#include "files.hpp"

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