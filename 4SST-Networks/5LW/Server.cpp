#include "Server.hpp"

using second_t = std::chrono::duration<double, std::ratio<1>>;

// Server side
Server::Server(fd binded, ServerOptions options)
{
    if (binded < 0)
        throw new std::runtime_error("Invalid socket fd");

    activeClient = std::list<sockaddr>();
    clientLastSeen = std::map<sockaddr, float>();
    socketFd = binded;
    noReply = options.noReply;
    this->options = options;
    if (options.method == ServerOptions::byTimeout)
        timer = Timer();
    pollFd[0].fd = socketFd;
    pollFd[0].events = POLLIN;
}
Server& Server::operator=(const Server& s)
{
    options = s.options;
    activeClient = s.activeClient;
    status = s.status;
    address = s.address;
    socketFd = s.socketFd;
    noReply = s.noReply;
    pollFd[0] = s.pollFd[0];
    clientLastSeen = s.clientLastSeen;
    if (status == ServiceStatus::Running) {
        Start();
    }
    return *this;
}
Server::Server(const Server& s)
{
    *this = s;
}

void Server::updateClientsByTimeout()
{
    double elapsed = timer.elapsed();
    for (auto i = activeClient.begin(); i != activeClient.end(); ++i) {
        if (elapsed - clientLastSeen[*i] > std::chrono::duration_cast<second_t>(options.timeout).count()) {
            activeClient.remove(*i);
        }
    }
}

void Server::updateClients(ClientServerMessage message, sockaddr address)
{
    switch (options.method) {
    case ServerOptions::byPacket:
        break;
    case ServerOptions::byTimeout:
        updateClientsByTimeout();
    default:
        break;
    }

    switch (message) {
    case ClientServerMessage::RUNNING:
        if (std::find(activeClient.begin(), activeClient.end(), address) == activeClient.end()) {
            activeClient.push_back(address);
        }

        if (options.method == ServerOptions::byTimeout) {
            if (clientLastSeen.find(address) == clientLastSeen.end())
                clientLastSeen.insert({ address, timer.elapsed() });
            else
                clientLastSeen[address] = timer.elapsed();
        }
        break;
    case ClientServerMessage::STOPPED:
        if (options.method == ServerOptions::byPacket && std::find(activeClient.begin(), activeClient.end(), address) == activeClient.end()) {
            activeClient.remove(address);
            clientLastSeen.erase(address);
        }
    default:
        break;
    }
}

void* get_in_addr(struct sockaddr* sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void Server::mainLoop(fd* socket, char s[INET6_ADDRSTRLEN], pollfd* pfd)
{
    buffer_t tmp;
    sockaddr_storage their_address;
    socklen_t addr_len = sizeof(their_address);
    int bytesReceived = -1;
    int err_count = 0;
    sockaddr* casted = reinterpret_cast<sockaddr*>(&their_address);

    while (status == ServiceStatus::Running) {

        int poll_result = poll(pfd, 1, 50);
        if (poll_result == -1) {
            perror("[Server] poll");
            if (err_count < 5)
                ++err_count;
            else
                throw "[Server] Too many poll errors";
            continue;
        } else if (poll_result == 0)
            continue;
        else {
            if (!(pollFd[0].revents & POLLIN))
                continue;

            if (options.debugOutput)
                std::cout << "[Server] Receive packet from " << inet_ntop(casted->sa_family, get_in_addr((struct sockaddr*)&casted), s, INET6_ADDRSTRLEN) << "\n";
            bytesReceived = recvfrom(*socket, tmp, sizeof(tmp), 0, casted, &addr_len); // receive normal data

            if (bytesReceived == -1) {
                perror("[Server] recvfrom");
                std::cerr << "[Server] Error occured in recvfrom\n";
                continue;
            }

            tmp[bytesReceived] = '\0';
            ClientServerMessage message = static_cast<ClientServerMessage>(std::atoi(tmp));
            updateClients(message, *casted);
        }
    }
    delete socket;
    delete pfd;
}

std::vector<std::string> Server::GetClients()
{
    std::vector<std::string> result = std::vector<std::string>();
    size_t length = activeClient.size();
    result.resize(length, std::string(INET6_ADDRSTRLEN, '\0'));

    auto current = activeClient.begin();
    for (size_t i = 0; i < length; ++i, ++current) {
        sockaddr_in* ipv4_addr = reinterpret_cast<sockaddr_in*>(&(*current));

        inet_ntop(AF_INET, ipv4_addr, result[i].data(), INET_ADDRSTRLEN);
    }

    return result;
}

void Server::Start()
{
    status = ServiceStatus::Running;
    char buffer[INET6_ADDRSTRLEN];
    pollfd* pollfdThread = new pollfd();
    *pollfdThread = pollFd[0];
    
    serverThread = std::thread(&Server::mainLoop, this, new fd(socketFd), buffer, pollfdThread);
}

void Server::Stop()
{
    status = ServiceStatus::Stopped;
    serverThread.join();
}

Server::~Server()
{
}
