#ifndef SERVER_LIB
#define SERVER_LIB

#include <algorithm>
#include <arpa/inet.h>
#include <chrono>
#include <iostream>
#include <list>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <shared_mutex>
#include <signal.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>
#include <unordered_map>
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
    sockaddr selfaddress;
    bool addSelfAddress = true;
};

class Server {
private:
    fd socketFd;
    sockaddr_in address;
    std::list<std::string> activeClient;
    std::shared_mutex activeClientMutex;
    ServiceStatus status = ServiceStatus::Stopped;
    ServerOptions options;
    Timer timer;
    bool noReply;
    pollfd pollFd[1];

    void mainLoop(fd* socket, char s[INET6_ADDRSTRLEN]);
    void updateClients(ClientServerMessage message, sockaddr_storage address);
    void updateClientsByTimeout();

public:
    Server() { }
    Server(fd binded, ServerOptions options);
    Server(const Server& s);
    void Read();
    void Start();
    void Stop();
    std::vector<std::string> GetClients() const;
    ServiceStatus GetStatus() const { return status; }

    Server& operator=(const Server&);

    ~Server();
};

#endif // SERVER_LIB