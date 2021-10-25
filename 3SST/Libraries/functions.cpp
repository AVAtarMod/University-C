#include <chrono>
#include <cstring>
#include <random>

#include "functions.hpp"

int getRandomNumber(int from, int to) {
    try {
        if (from > to)
            throw "Incorrect couple 'from - to' for generating random numbers";
    } catch (const char* message) {
        std::cerr << message << '\n';
        exit(1);
    }

    unsigned int now = static_cast<unsigned>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count() %
        10000);
    std::mt19937 engine(now);
    std::uniform_int_distribution<int> random(from, to);

    return random(engine);
}

void replace(char* string, int* indexes, int lnIndexes, char symbol) {
    for (int i = 0; i < lnIndexes; i++) {
        int currentIndex = indexes[i];
        string[currentIndex] = symbol;
    }
}

int* indexSymbols(char* string, char symbol, int& count) {
    int newLen = 0;
    int length = strlen(string);
    for (int iCh = 0; iCh < length; iCh++) {
        if (string[iCh] == symbol)
            newLen++;
    }
    count = newLen;
    int* indexes = nullptr;

    if (newLen > 0) {
        indexes = new int[newLen];

        int iIndexes = 0;
        for (int iCh = 0; iCh < length; iCh++) {
            if (string[iCh] == symbol) {
                indexes[iIndexes] = iCh;
                iIndexes++;
            }
        }
    }

    return indexes;
}

int getNumberDigits(int number) {
    int numberDigits = 0;
    while (number != 0) {
        ++numberDigits;
        number /= 10;
    }
    return numberDigits;
}
