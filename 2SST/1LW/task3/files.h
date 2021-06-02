#ifndef FILES
#define FILES

void readArray(int **array, int rows, int collumns, const char *filename, const int readPosition);
std::vector<int> readSearchFile(const char *filename);
bool isFileExist(const char *file);

#endif