#include <iostream>

#include "ClientServer.hpp"

int task1();
int task2();

int main(int argc, char const* argv[])
{
    bool noData = false;
    if (argc == 1) {
        std::cout << "Введите программу для запуска: ";
        argc++;
        noData = true;
    }

    int exit_code = 0;

    for (int i = 1; i < argc; i++) {
        int choice;
        if (noData) {
            std::cin >> choice;
            std::cin.ignore(32767, '\n');
        } else {
            choice = std::stoi(argv[i]);
        }

        switch (choice) {
        case 1:
            std::cout << "Вариант №1\n";
            exit_code += task1();
            std::cout << "-----\n";
            break;
        case 2:
            std::cout << "Вариант №2\n";
            exit_code += task2();
            std::cout << "-----\n";
            break;
        default:
            std::cout << "Номер задачи введён не верно либо не удалось конвертировать введённые данные\n";
            break;
        }
    }

    return exit_code;
}

std::string vectorToText(std::vector<std::string> vector)
{
    if (vector.size() > 0) {
        std::string result = "Clients:\n";
        for (std::string& i : vector) {
            result += "    " + i + "\n";
        }
        return result;
    }
    return "";
}

void cleanConsole(int linesCount)
{
    if (linesCount > 0) {
        for (int i = 0; i < linesCount; i++) {
            if (i < linesCount - 1)
                std::cout << "\x1b[1F";
            std::cout << "\x1b[2K";
        }
        for (int i = 0; i < linesCount; i++) {
            std::cout << "\x1b[1F";
        }
    }
}

int charCount(std::string source, char c)
{
    size_t lenght = source.size();
    int count = 0;
    for (size_t i = 0; i < lenght; i++) {
        if (source[i] == c)
            ++count;
    }
    return count;
}

int task1()
{
    int port;
    std::cout << "Enter port: ";
    std::cin >> port;
    bool debug = false;
    cleanConsole(1);
    std::cout << "Enable debug (1 or 0): ";
    std::cin >> debug;
    
    ServerOptions serverOpts = ServerOptions();
    serverOpts.method = ServerOptions::byPacket;
    serverOpts.debugOutput = debug;
    ClientOptions clientOpts = ClientOptions();
    clientOpts.timeout = std::chrono::milliseconds(500);
    clientOpts.sendByTimeout = true;
    clientOpts.useBroadcast = true;
    clientOpts.debugOutput = debug;

    ClientServer cs = ClientServer(serverOpts, clientOpts, port);
    cs.Start();

    char key;
    bool exit = false;
    int bufferLinesCount = -1;
    while (!exit) {
        cleanConsole(bufferLinesCount);
        std::string buffer = vectorToText(cs.GetClients());
        bufferLinesCount = charCount(buffer, '\n');

        std::cout << buffer << "Enter e for exit: ";
        std::cin >> key;
        if (key == 'e')
            exit = true;
    }
    cs.Stop();

    return 0;
}
int task2()
{
    ServerOptions serverOpts = ServerOptions();
    serverOpts.method = ServerOptions::byTimeout;
    serverOpts.timeout = std::chrono::milliseconds(1000);
    ClientOptions clientOpts = ClientOptions();
    clientOpts.timeout = std::chrono::milliseconds(200);
    clientOpts.sendByTimeout = true;
    clientOpts.useBroadcast = true;

    ClientServer cs = ClientServer(serverOpts, clientOpts, 7000);
    cs.Start();
    char key;
    bool exit = false;
    int bufferLinesCount = -1;
    while (!exit) {
        cleanConsole(bufferLinesCount);
        std::string buffer = vectorToText(cs.GetClients());
        bufferLinesCount = charCount(buffer, '\n');

        std::cout << buffer << "Enter e for exit: ";
        std::cin >> key;
        if (key == 'e')
            exit = true;
    }
    cs.Stop();
    return 0;
}
