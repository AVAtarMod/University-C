#ifndef CLIENT_SERVER_LIB
#define CLIENT_SERVER_LIB

#include "Client.hpp"
#include "Server.hpp"
#include "Types.hpp"
#include <exception>
#include <fcntl.h>

class ClientServer {
private:
    Client client;
    Server server;
    ServiceStatus status;
    int port;
    bool serverDebug = false, clientDebug = false;

    fd InitClientSocket();
    fd InitServerSocket();

public:
    // TODO add support non broadcast address for client
    // TODO add support protocol string
    ClientServer(ServerOptions serverOptions, ClientOptions clientOptions, int port);
    void Start();
    void Stop();
    std::vector<std::string> GetClients();
    ServiceStatus GetStatus();
    ~ClientServer();
};

#endif // CLIENT_SERVER_LIB
