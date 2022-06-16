#include "Server.hpp"

using second_t = std::chrono::duration<double, std::ratio<1>>;
void* get_in_addr(sockaddr* sa);

// Server side
Server::Server(fd binded, ServerOptions options)
{
    if (binded < 0)
        throw new std::runtime_error("Invalid socket fd");

    activeClient = std::list<std::string>();
    clientLastSeen = std::unordered_map<std::string, float>();
    socketFd = binded;
    noReply = options.noReply;
    this->options = options;
    if (options.method == ServerOptions::byTimeout)
        timer = Timer();
    pollFd[0].fd = socketFd;
    pollFd[0].events = POLLIN;
    pollFd[0].revents = 0;
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
    std::shared_lock lock(activeClientMutex);
    double elapsed = timer.elapsed();
    for (auto i = activeClient.cbegin(); i != activeClient.cend();) {
        if (elapsed - clientLastSeen[*i] > std::chrono::duration_cast<second_t>(options.timeout).count()) {
            clientLastSeen.erase(*i);
            activeClient.remove(*i);
        } else
            ++i;
    }
}

std::string to_string(sockaddr addr)
{
    std::string result = std::string(INET6_ADDRSTRLEN, '\0');
    inet_ntop(addr.sa_family,
        get_in_addr(&addr),
        result.data(), result.size());
    result.shrink_to_fit();
    return result;
}

void Server::updateClients(ClientServerMessage message, sockaddr address)
{
    // bool needUpdateByTimeout = false;
    switch (options.method) {
    case ServerOptions::byPacket:
        break;
    // case ServerOptions::byTimeout:
        // needUpdateByTimeout = true;
    default:
        break;
    }
    std::string strAddress = to_string(address);

    switch (message) {
    case ClientServerMessage::RUNNING:
        if (std::find(activeClient.begin(), activeClient.end(), strAddress) == activeClient.end()) {
            std::shared_lock lock(activeClientMutex);
            activeClient.push_back(strAddress);
        }

        if (options.method == ServerOptions::byTimeout) {
            if (clientLastSeen.find(strAddress) == clientLastSeen.end())
                clientLastSeen.insert({ strAddress, timer.elapsed() });
            else
                clientLastSeen[strAddress] = timer.elapsed();
        }
        break;
    case ClientServerMessage::STOPPED:
        if (options.method == ServerOptions::byPacket && std::find(activeClient.begin(), activeClient.end(), strAddress) == activeClient.end()) {
            std::shared_lock lock(activeClientMutex);
            activeClient.remove(strAddress);
            clientLastSeen.erase(strAddress);
        }
    default:
        break;
    }

    // if (needUpdateByTimeout)
    //     updateClientsByTimeout();
}

void* get_in_addr(sockaddr* sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((sockaddr_in*)sa)->sin_addr);
    }

    return &(((sockaddr_in6*)sa)->sin6_addr);
}

void initBuffer(buffer_t buffer)
{
    for (size_t i = 0; i < sizeof(buffer_t); ++i) {
        buffer[i] = '\0';
    }
}

void Server::mainLoop(fd* socket, char s[INET6_ADDRSTRLEN])
{
    buffer_t tmp;
    initBuffer(tmp);
    sockaddr_storage their_address;
    socklen_t addr_len = sizeof(their_address);
    int bytesReceived = -1;
    int err_count = 0;
    sockaddr* casted = reinterpret_cast<sockaddr*>(&their_address);

    int poll_result = 0;
    while (status == ServiceStatus::Running) {

        poll_result = poll(pollFd, 1, 500);
        if (poll_result == -1) {
            perror("[Server] poll");
            if (err_count < 5)
                ++err_count;
            else
                throw std::runtime_error("[Server] Too many poll errors");
            continue;
        } else if (poll_result == 0)
            continue;
        else {
            if (!(pollFd[0].revents & POLLIN))
                continue;

            if (options.debugOutput)
                std::cout << "[Server] Receive packet from " << inet_ntop(casted->sa_family, get_in_addr(casted), s, INET6_ADDRSTRLEN) << "\n";
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
}

std::vector<std::string> Server::GetClients()
{
    std::vector<std::string> result = std::vector<std::string>();
    {
        std::shared_lock lock(activeClientMutex);
        size_t length = activeClient.size();
        result.resize(length);

        size_t index = 0;
        for (auto i = activeClient.cbegin(); i != activeClient.cend(); ++i, ++index) {
            result[index] = *i;
        }
    }

    return result;
}

void Server::Start()
{
    status = ServiceStatus::Running;
    char buffer[INET6_ADDRSTRLEN];
    serverThread = std::thread(&Server::mainLoop, this, new fd(socketFd), buffer);
}

void Server::Stop()
{
    status = ServiceStatus::Stopped;
    serverThread.join();
}

Server::~Server()
{
}
