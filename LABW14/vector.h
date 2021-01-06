#ifndef VECTOR
#define VECTOR

#include <vector>

#include "struct.h"

std::vector<Member> userInput();

void print(std::vector<Member> members, const char *text = "");
void deleteMember(std::vector<Member> &storage);
void sort(std::vector<Member> &storage);

void binPrint(std::string file, std::vector<Member> storage);
void binInput(std::string file, std::vector<Member> &storage, bool readUntilEof);
void binOutput(std::string file, std::vector<Member> storage);

void txtOutput(std::string file, std::vector<Member> str);

bool isEmpty(std::vector<Member> str)
{
    bool result = str.empty();
    if (result) std::cerr << "Array members is empty. NOTE: act #9 not save data to array.\n";
    return result;
}
#endif