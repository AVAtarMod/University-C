#ifndef CLIENT_LIB
#define CLIENT_LIB

#include "Types.hpp"
#include <arpa/inet.h>
#include <chrono>
#include <cstring>
#include <iostream>
#include <list>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>

class ClientOptions {
public:
    bool useBroadcast = true;
    bool sendByTimeout = false;
    bool notifyServersOnStop;
    bool debugOutput;

    std::chrono::milliseconds timeout;
};

class Client {
private:
    fd socketFd;
    hostent destination;
    int port;
    std::list<sockaddr> listeners;
    ServiceStatus status = ServiceStatus::Stopped;
    ClientOptions options;

    void InitTheirAddr(sockaddr_in& addr);
    void sendMessage(const char* message);

public:
    Client()
    {
    }
    Client(fd binded, ClientOptions options, int port, hostent destination);
    Client(const Client& c);
    void Start();
    void Stop();
    void Send();
    void SendReply();
    ServiceStatus GetStatus() const { return status; }

    Client& operator=(const Client& c);

    ~Client();
};

#endif // CLIENT_LIB
