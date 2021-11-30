#ifndef USEFUL
#define USEFUL

#include <iostream>
#include <string>

template <class T> T printAndScan(const char* text = "") {
    T data;
    std::cout << text;
    std::cin >> data;
    std::cin.ignore(32767, '\n');
    return data;
}

void cinReset();

extern std::string reset;

// Black
extern std::string fgBlack;
extern std::string fgBrightBlack;
extern std::string bgBlack;
extern std::string bgBrightBlack;

// Red
extern std::string fgRed;
extern std::string fgBrightRed;
extern std::string bgRed;
extern std::string bgBrightRed;

// Green
extern std::string fgGreen;
extern std::string fgBrightGreen;
extern std::string bgGreen;
extern std::string bgBrightGreen;

// Yellow
extern std::string fgYellow;
extern std::string fgBrightYellow;
extern std::string bgYellow;
extern std::string bgBrightYellow;

// Blue
extern std::string fgBlue;
extern std::string fgBrightBlue;
extern std::string bgBlue;
extern std::string bgBrightBlue;

// Magenta
extern std::string fgMagenta;
extern std::string fgBrightMagenta;
extern std::string bgMagenta;
extern std::string bgBrightMagenta;

// Cyan
extern std::string fgCyan;
extern std::string fgBrightCyan;
extern std::string bgCyan;
extern std::string bgBrightCyan;

// White
extern std::string fgWhite;
extern std::string fgBrightWhite;
extern std::string bgWhite;
extern std::string bgBrightWhite;

#endif
