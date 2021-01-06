#ifndef VECTOR
#define VECTOR

#include <vector>

#include "struct.h"

std::vector<Member> userInput();
void binInput(std::string file, std::vector<Member> &storage, bool readUntilEof);

void print(std::vector<Member>);
void binOutput(std::string file, std::vector<Member> storage);

#endif