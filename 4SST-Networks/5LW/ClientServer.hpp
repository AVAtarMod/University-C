#ifndef CLIENT_SERVER_LIB
#define CLIENT_SERVER_LIB

#include "Client.hpp"
#include "Server.hpp"
#include "Types.hpp"

#include <exception>

class ClientServer {
private:
    Client client;
    Server server;
    ServiceStatus status;
    int port;

    fd InitClientSocket(const char* name);
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
