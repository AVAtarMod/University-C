#ifndef VECTOR
#define VECTOR

#include <vector>

#include "struct.h"

std::vector<Member> userInput();
void binInput(const char *file, std::vector<Member> storage, bool readUntilEof);

void print(std::vector<Member>);
void binOutput(const char *file, std::vector<Member> storage);

#endif