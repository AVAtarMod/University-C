#ifndef VECTOR
#define VECTOR

#include <vector>

#include "struct.h"

void userInput(std::vector<Member> members);

void print(std::vector<Member> members, const char *text = "");
void deleteElement(std::vector<Member> &storage);
void sort(std::vector<Member> &storage);
void find(std::vector<Member> storage);
void edit(std::vector<Member> &storage);

void finalAct(std::vector<Member> &storage, const char *text = "");

void binPrint(std::string file, std::vector<Member> storage);
void binInput(std::string file, std::vector<Member> &storage, bool readUntilEof);
void binOutput(std::string file, std::vector<Member> storage);

void txtOutput(std::string file, std::vector<Member> str);

bool isEmpty(std::vector<Member> str, int act);

#endif