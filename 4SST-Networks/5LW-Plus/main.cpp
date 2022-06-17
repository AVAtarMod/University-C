#include <iostream>
#include <signal.h>

#include "ClientServer.hpp"

sig_atomic_t stopFlag = 0;

int task1(bool debug);
int task2(bool debug);

void sigintHandler(int)
{
    stopFlag = 1;
}

int main(int argc, char const* argv[])
{
    std::cout << "Send SIGINT signal inside task to stop it\n";
    bool noData = false;
    if (argc == 1) {
        std::cout << "Введите программу для запуска и ее параметры: ";
        argc++;
        noData = true;
    }

    int exit_code = 0;

    signal(SIGINT, sigintHandler);

    for (int i = 1; i < argc; i++) {
        bool debug = false;
        int choice;
        if (noData) {
            std::cin >> choice;
            std::cin.ignore(32767, '\n');
        } else {
            choice = std::stoi(argv[i]);
        }

        if ((choice == 1 || choice == 2) && i < argc - 1 && strcmp(argv[i + 1], "-d") == 0) {
            debug = true;
            ++i;
        }
        switch (choice) {
        case 1:
            std::cout << "Вариант №1\n";
            exit_code += task1(debug);
            std::cout << "-----\n";
            break;
        case 2:
            std::cout << "Вариант №2\n";
            exit_code += task2(debug);
            std::cout << "-----\n";
            break;
        default:
            std::cout << "Номер задачи введён не верно либо не удалось конвертировать введённые данные\n";
            break;
        }
        if (stopFlag == 1)
            stopFlag = 0;
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

void clientServerLoop(ClientServer& cs)
{
    cs.Start();
    std::string buffer = "";
    // int bufferLinesCount = -1;
    while (stopFlag == 0) {
        // cleanConsole(bufferLinesCount);
        cs.ServerRead();
        cs.ClientSend();
        std::cout << buffer;
        // bufferLinesCount = charCount(buffer, '\n');
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << "Closing sockets...\n";

    cs.Stop();
}

int task1(bool debug)
{
    int port;
    std::cout << "Enter port: ";
    std::cin >> port;

    ServerOptions serverOpts = ServerOptions();
    serverOpts.method = ServerOptions::byPacket;
    serverOpts.debugOutput = debug;
    ClientOptions clientOpts = ClientOptions();
    clientOpts.timeout = std::chrono::milliseconds(500);
    clientOpts.sendByTimeout = true;
    clientOpts.useBroadcast = true;
    clientOpts.debugOutput = debug;

    ClientServer cs = ClientServer(serverOpts, clientOpts, port);
    clientServerLoop(cs);

    return 0;
}
int task2(bool debug)
{
    return 0;

    int port;
    std::cout << "Enter port: ";
    std::cin >> port;

    ServerOptions serverOpts = ServerOptions();
    serverOpts.method = ServerOptions::byTimeout;
    serverOpts.timeout = std::chrono::milliseconds(1500);
    serverOpts.debugOutput = debug;

    ClientOptions clientOpts = ClientOptions();
    clientOpts.timeout = std::chrono::milliseconds(500);
    clientOpts.sendByTimeout = true;
    clientOpts.useBroadcast = true;
    clientOpts.debugOutput = debug;

    ClientServer cs = ClientServer(serverOpts, clientOpts, port);
    clientServerLoop(cs);

    return 0;
}
