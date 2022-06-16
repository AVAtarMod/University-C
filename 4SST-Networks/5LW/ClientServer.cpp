#include "ClientServer.hpp"

fd ClientServer::InitClientSocket(const char* name)
{
    fd clientSocket;

    int broadcast = 1;

    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == -1) {
        perror("socket");

        throw new std::runtime_error("Cannot create client socket");
    }

    // this call is what allows broadcast packets to be sent:
    if (setsockopt(clientSocket, SOL_SOCKET, SO_BROADCAST, &broadcast,
            sizeof broadcast)
        == -1) {
        perror("setsockopt (SO_BROADCAST)");

        throw new std::runtime_error("Cannot set client broadcast mode");
    }
    return clientSocket;
}

fd ClientServer::InitServerSocket()
{
    fd serverSocket;
    struct addrinfo hints, *servinfo, *p;
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; // set to AF_INET to use IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(nullptr, std::to_string(port).c_str(), &hints, &servinfo)) != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(rv) << std::endl;
        throw new std::runtime_error("Cannot get local address info");
    }

    // loop through all the results and bind to the first we can
    for (p = servinfo; p != nullptr; p = p->ai_next) {
        serverSocket = socket(p->ai_family, p->ai_socktype,
            p->ai_protocol);

        if (serverSocket == -1) {
            perror("listener: socket");
            throw new std::runtime_error("Cannot creaete server socket");
        }

        if (bind(serverSocket, p->ai_addr, p->ai_addrlen) == -1) {
            close(serverSocket);
            perror("listener: bind");
            continue;
        }

        break;
    }

    if (p == nullptr) {
        std::cerr << "listener: failed to bind socket\n";
        throw new std::runtime_error("Cannot bind server socket");
    }

    freeaddrinfo(servinfo);
    return serverSocket;
}

ClientServer::ClientServer(ServerOptions serverOptions, ClientOptions clientOptions, int port)
{
    status = ServiceStatus::Stopped;
    const char* name = "255.255.255.255";

    struct hostent* he = gethostbyname(name);
    if (he == nullptr) { // get the host info
        perror("gethostbyname");
        throw new std::runtime_error("Cannot get host by name");
    }

    fd clientSocket = InitClientSocket(name);
    fd serverSocket = InitServerSocket();

    server = Server(serverSocket, serverOptions);

    client = Client(clientSocket, clientOptions, port, *he);
}

void ClientServer::Start()
{
    server.Start();
    client.Start();
}
void ClientServer::Stop()
{
    client.Stop();
    server.Stop();
}
std::vector<std::string> ClientServer::GetClients()
{
    return server.GetClients();
}
ServiceStatus ClientServer::GetStatus()
{
    if (server.GetStatus() == ServiceStatus::Running && client.GetStatus() == ServiceStatus::Running)
        return ServiceStatus::Running;
    else
        return ServiceStatus::Stopped;
}
ClientServer::~ClientServer()
{
    if (status == ServiceStatus::Running)
        Stop();
}
