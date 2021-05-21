#ifndef USEFUL
#define USEFUL

#include <iostream>

template<class T>
T printAndScan(const char* text){
    T data;
    std::cout << text;
    std::cin >> data;
    std::cin.ignore(32767, '\n');

    return data;
}

std::string reset = "\033[0m";

// Black
std::string fgBlack = "\033[30m";
std::string fgBrightBlack = "\033[30;1m";
std::string bgBlack = "\033[40m";
std::string bgBrightBlack = "\033[40;1m";

// Red
std::string fgRed = "\033[31m";
std::string fgBrightRed = "\033[31;1m";
std::string bgRed = "\033[41m";
std::string bgBrightRed = "\033[41;1m";

// Green
std::string fgGreen = "\033[32m";
std::string fgBrightGreen = "\033[32;1m";
std::string bgGreen = "\033[42m";
std::string bgBrightGreen = "\033[42;1m";

// Yellow
std::string fgYellow = "\033[33m";
std::string fgBrightYellow = "\033[33;1m";
std::string bgYellow = "\033[43m";
std::string bgBrightYellow = "\033[43;1m";

// Blue
std::string fgBlue = "\033[34m";
std::string fgBrightBlue = "\033[34;1m";
std::string bgBlue = "\033[44m";
std::string bgBrightBlue = "\033[44;1m";

// Magenta
std::string fgMagenta = "\033[35m";
std::string fgBrightMagenta = "\033[35;1m";
std::string bgMagenta = "\033[45m";
std::string bgBrightMagenta = "\033[45;1m";

// Cyan
std::string fgCyan = "\033[36m";
std::string fgBrightCyan = "\033[36;1m";
std::string bgCyan = "\033[46m";
std::string bgBrightCyan = "\033[46;1m";

// White
std::string fgWhite = "\033[37m";
std::string fgBrightWhite = "\033[37;1m";
std::string bgWhite = "\033[47m";
std::string bgBrightWhite = "\033[47;1m";

#endif