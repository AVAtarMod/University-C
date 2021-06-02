#ifndef FUNCTIONS
#define FUNCTIONS

#include <string>
#include <fstream>

#include "arrays2d.h"

std::string task1(const char*filename);

/**
 * @brief Solve normal magickSquare
 * 
 * @param size default is 3x3, must be > 1x1
 * @return Solved square (int**)
 */
int **magickSquare(int size[2] = nullptr);
    
#endif //FUNCTIONS