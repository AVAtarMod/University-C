#include "ClientServer.hpp"

fd ClientServer::InitClientSocket()
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

        throw new std::runtime_error("[Client] Cannot set client broadcast mode");
    }
    return clientSocket;
}

fd ClientServer::InitServerSocket()
{
    fd serverSocket;
    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET6; // set to AF_INET to use IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
    if (serverDebug)
        std::cout << "[D] [Server] Socket init: use " << std::to_string(port).c_str() << " port for bind\n";

    int rv = getaddrinfo(nullptr, std::to_string(port).c_str(), &hints, &servinfo);

    if (rv != 0) {
        std::cerr << "[Server] getaddrinfo: " << gai_strerror(rv) << std::endl;
        throw new std::runtime_error("Cannot get local address info");
    }
    int yes = 1;
    // loop through all the results and bind to the first we can
    for (p = servinfo; p != nullptr; p = p->ai_next) {
        serverSocket = socket(p->ai_family, p->ai_socktype,
            p->ai_protocol);

        if (serverSocket == -1) {
            perror("[Server] socket");
            throw new std::runtime_error("Cannot creaete server socket");
        }

        setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

        int bind_result = bind(serverSocket, p->ai_addr, p->ai_addrlen);

        if (bind_result == -1) {
            close(serverSocket);
            perror("[Server] bind");
            continue;
        }

        serverAddress = *(p->ai_addr);

        break;
    }
    std::cout << "[D] [Server] Socket created successfuly\n";
    if (p == nullptr) {
        std::cerr << "[Server] Error: failed to bind socket\n";
        throw new std::runtime_error("Cannot bind server socket");
    }

    freeaddrinfo(servinfo);
    std::cout << "[D] [Server] Unused adresses freed\n";
    return serverSocket;
}

void ClientServer::ServerRead()
{
    server.Read();
}

void ClientServer::ClientSend()
{
    client.Send();
}

ClientServer::ClientServer(ServerOptions serverOptions, ClientOptions clientOptions, int port)
{
    this->port = port;
    status = ServiceStatus::Stopped;
    const char* name = "255.255.255.255";

    struct hostent* he = gethostbyname(name);
    if (he == nullptr) { // get the host info
        perror("gethostbyname");
        throw new std::runtime_error("Cannot get host by name");
    }

    if (serverOptions.debugOutput)
        serverDebug = true;
    if (clientOptions.debugOutput)
        clientDebug = true;

    fd clientSocket = InitClientSocket();
    fd serverSocket = InitServerSocket();

    serverOptions.selfaddress = serverAddress;

    client = Client(clientSocket, clientOptions, port, *he);

    server = Server(serverSocket, serverOptions);
}

void ClientServer::Start()
{
    server.Start();
    client.Start();
}
void ClientServer::Stop()
{
    server.Stop();
    client.Stop();
}
std::vector<std::string> ClientServer::GetClients() const
{
    return server.GetClients();
}
ServiceStatus ClientServer::GetStatus() const
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
