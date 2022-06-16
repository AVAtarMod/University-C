#ifndef SERVER_LIB
#define SERVER_LIB

#include <algorithm>
#include <arpa/inet.h>
#include <chrono>
#include <iostream>
#include <list>
#include <map>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>
#include <vector>

#include "Timer.hpp"
#include "Types.hpp"

class ServerOptions {
public:
    enum ClientStatusCheckMethod {
        byTimeout,
        byPacket
    } method
        = byPacket;
    bool noReply = true;
    bool debugOutput = false;
    std::chrono::milliseconds timeout;
};

class Server {
private:
    fd socketFd;
    sockaddr_in address;
    std::list<sockaddr> activeClient;
    std::map<sockaddr, float> clientLastSeen;
    ServiceStatus status = ServiceStatus::Stopped;
    std::thread serverThread;
    ServerOptions options;
    Timer timer;
    bool noReply;
    pollfd pollFd[1];

    void mainLoop(fd* socket, char s[INET6_ADDRSTRLEN], pollfd* pfd);
    void updateClients(ClientServerMessage message, sockaddr address);
    void updateClientsByTimeout();

public:
    Server() { }
    Server(fd binded, ServerOptions options);
    Server(const Server& s);
    void Start();
    void Stop();
    std::vector<std::string> GetClients();
    ServiceStatus GetStatus() { return status; }

    Server& operator=(const Server&);

    ~Server();
};

#endif // SERVER_LIB
